import tkinter as tk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import matplotlib.pyplot as plt
import serial
import threading
import numpy as np
import time

# Serial settings
SERIAL_PORT = 'COM5'   # ← change to your port
BAUD_RATE   = 115200

# Data buffers
max_points = 100
data1, data2, data3 = [], [], []

# Thread control
running = threading.Event()
running.set()

# Initialize serial port with a short timeout
try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=0.1)
except Exception as e:
    print(f"Could not open serial port: {e}")
    ser = None

def read_serial():
    """Continuously read, parse, and enqueue data while running is set."""
    while running.is_set():
        if ser and ser.in_waiting > 0:
            try:
                line = ser.readline().decode(errors='ignore').strip()
                print(line)
                parts = line.split(',')
                if len(parts) == 3:
                    vals = []
                    for p in parts:
                        try:
                            vals.append(float(p))
                        except ValueError:
                            break
                    else:
                        for buf, v in zip((data1, data2, data3), vals):
                            buf.append(v)
                            if len(buf) > max_points:
                                buf.pop(0)
                        root.after(0, update_plot)
            except Exception as e:
                print(f"Serial read error: {e}")
        else:
            time.sleep(0.01)

def update_plot():
    """Update Matplotlib lines, labels, and dynamic Y-limits."""
    n = len(data1)
    if n < max_points:
        xs = list(range(n))
    else:
        xs = list(range(n - max_points, n))

    # Update each line
    for i, (line, buf) in enumerate(zip(lines, (data1, data2, data3))):
        ys = buf[-max_points:]
        line.set_data(xs, ys)
        if ys:
            value_labels[i]['text'] = f"Data {i+1}: {ys[-1]:.2f}"

    # Compute the displayed window's maximum value across all three buffers
    # If no data, default to 1.0 to avoid zero-span
    window_vals = []
    for buf in (data1, data2, data3):
        window_vals.extend(buf[-max_points:])
    if window_vals:
        y_max = max(window_vals) * 1.05
    else:
        y_max = 1.0

    # Apply dynamic limits
    if xs:
        ax.set_xlim(xs[0], xs[-1])
    ax.set_ylim(0, y_max)

    canvas.draw_idle()

def quit_app():
    """Stop thread, close serial, and exit cleanly."""
    running.clear()
    reader_thread.join(timeout=1.0)
    if ser and ser.is_open:
        ser.close()
    root.quit()
    root.destroy()

# ——— GUI Setup ———
root = tk.Tk()
root.title("Arduino Real-Time Plot")
root.attributes('-fullscreen', True)
root.bind('<Escape>', lambda e: root.attributes('-fullscreen', False))

# Matplotlib figure & axes
fig, ax = plt.subplots(figsize=(10, 4))
lines = [ax.plot([], [], label=f'Data {i+1}')[0] for i in range(3)]
ax.set_xlim(0, max_points)
ax.set_ylim(0, 1)  # will be updated on first draw
ax.legend(loc='upper right')
ax.set_xlabel("Sample #")
ax.set_ylabel("Value")
ax.set_title("Real-Time Arduino Data")

canvas = FigureCanvasTkAgg(fig, master=root)
canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)

# Bottom frame: labels + quit button
bottom = tk.Frame(root)
bottom.pack(pady=8)
value_labels = []
for i in range(3):
    lbl = tk.Label(bottom, text=f"Data {i+1}: N/A", font=('Helvetica', 16))
    lbl.grid(row=0, column=i, padx=30)
    value_labels.append(lbl)

quit_btn = tk.Button(bottom, text="Quit", font=('Helvetica',14), bg='red', fg='white',
                     command=quit_app)
quit_btn.grid(row=0, column=3, padx=20)

root.protocol("WM_DELETE_WINDOW", quit_app)

# ——— Start background reader thread ———
reader_thread = threading.Thread(target=read_serial, daemon=False)
reader_thread.start()

# ——— Run ———
root.mainloop()
