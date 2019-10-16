int data;
long unsigned int totaldata;
char dataL[4],dataR[4], dataD[4];
void setup() {
  Serial.begin(9600);
         pinMode(9,OUTPUT);
         pinMode(8,OUTPUT);
         pinMode(10,OUTPUT);
         pinMode(7,OUTPUT);
}
void loop() {
  if(Serial.available() > 0) {
    char buffer[] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}; // Receive up to 1 bytes
                while (!Serial.available()); // Wait for characters
                Serial.readBytesUntil('\0', buffer, 19);
                  int x=0,i=0,j=0,y=0,val3=0,val4=0;
                  while(buffer[i]!=' ')
                 {
                   dataL[x]=buffer[i];
                   i++;
                   x++;
                 }
                   dataL[x]='\0';
                    i++;
                 
                 while(buffer[i]!=' ')
                 {
                   dataR[j]=buffer[i];
                   i++;
                   j++;
                 }
                   dataR[j]='\0';
                   i++;
                 if(buffer[i]=='1')
                   val3=1;
                 i=i+2;
                 if(buffer[i]=='1')
                    val4=1;
                 
                 int val1 = atoi(dataL);
                 int val2 = atoi(dataR);
                 
                 //dataD=totaldata%1000;
                 //totaldata
                
                val1=(int(val1/10))*10;
                val2=(int(val2/10))*10;
                
                Serial.print(val1);
                Serial.print(",");
                Serial.print(val2);
                Serial.print("'");
                Serial.print(val3);
                Serial.print("'");
                Serial.println(val4);
                analogWrite(9,val1);
                analogWrite(10,val2); 
                digitalWrite(5,val3);
                digitalWrite(6,val4);
  }
   
}
