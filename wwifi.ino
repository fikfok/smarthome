// библиотека для работы программного Serial
#include <SoftwareSerial.h>

// serial-порт к которому подключён Wi-Fi модуль
#define WIFI_SERIAL    mySerial

// библиотека для работы с датчиками MQ (Troyka-модуль)
#include <TroykaMQ.h>
 
// имя для пина, к которому подключен датчик
#define PIN_MQ135  A0

// создаём объект для работы с датчиком и передаём ему номер пина
MQ135 mq135(PIN_MQ135);

// создаём объект для работы с программным Serial
// и передаём ему пины TX и RX
SoftwareSerial mySerial(8, 9);
String wifiSpot = String("mgts148");
String wifiPassword = String("7595191000");
String host = String("192.168.100.5");
String port = String("8000");
int countTrueCommand;
int countTimeCommand;
boolean found = false;
double valSensor = 1;
int tmp = 1;

void setup()
{
  // открываем последовательный порт для мониторинга действий в программе
  // и передаём скорость 9600 бод
  Serial.begin(9600);
  
  while (!Serial) {
  // ждём, пока не откроется монитор последовательного порта
  // для того, чтобы отследить все события в программе
  }
  Serial.print("Serial init OK\r\n");
  // открываем Serial-соединение с Wi-Fi модулем на скорости 9600 бод
  WIFI_SERIAL.begin(9600);

  sendCommand("AT", 20, "OK");
  sendCommand("AT+CWMODE_DEF=3", 20, "OK");
  sendCommand("AT+UART_DEF=9600,8,1,0,0", 20, "OK");
  sendCommand("AT+CWJAP=\"" + wifiSpot + "\",\"" + wifiPassword + "\"", 20, "OK");

  // перед калибровкой датчика прогрейте его 60 секунд
  // выполняем калибровку датчика на чистом воздухе
  mq135.calibrate();
}

void loop()
{
 String body = "{\"temperature\":" + String(tmp) + ",\"carbon_dioxide\":" + String(mq135.readCO2()) + "}";
 
 String postData = "POST /metrics/ HTTP/1.1\r\n";
 postData += "Host: 192.168.100.5:8000\r\n";
 postData += "Content-Type: application/json\r\n";
 postData += "Accept: */*\r\n";
 postData += "Content-Length:" + String(body.length()) + "\r\n\r\n";
 postData += body;
 postData += "\r\n\r\n";

 sendCommand("AT+CIPSTART=\"TCP\",\"" + host + "\"," + port, 35, "OK");
 sendCommand("AT+CIPSEND=" + String(postData.length() + 4), 20, ">");
 WIFI_SERIAL.print(postData);

 delay(10000);
}

void sendCommand(String command, int maxTime, char readReplay[]) {
//  Serial.print(countTrueCommand);
//  Serial.print(". at command => ");
//  Serial.print(command);
//  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    WIFI_SERIAL.println(command);//at+cipsend
    if(WIFI_SERIAL.find(readReplay))//ok
    {
      found = true;
      break;
    }
 
    countTimeCommand++;
  }
 
  if(found == true)
  {
//    Serial.println("Done");
    countTrueCommand++;
    countTimeCommand = 0;
  }
 
  if(found == false)
  {
//    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
 
  found = false;
 }
