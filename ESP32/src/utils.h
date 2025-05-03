float pH = 0;
float DO = 0;
float temp = 0;

void parseData(String data){
    int firstComma = data.indexOf(',');
    int secondComma = data.indexOf(',', firstComma + 1);

    if (firstComma > 0 && secondComma > firstComma) {
      pH = data.substring(0, firstComma).toFloat();
      DO = data.substring(firstComma + 1, secondComma).toFloat();
      temp = data.substring(secondComma + 1).toFloat();
    }
    
}

