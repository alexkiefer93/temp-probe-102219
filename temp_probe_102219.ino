const int sensor0 = A0;
const int sensor1 = A1;
//const int sensor2 = A2;
//const int sensor3 = A3;

int val0 = 0;
int val1 = 0;
int adcBitDepth = 10;
float ambTemp = 72.0;             // ambient temp
float mv0 = 0.0;                  // voltage at probe 0
float mv1 = 0.0;
float temp0 = 0.0;                // temperature at probe 0
float temp1 = 0.0;
float temp0c = 0.0;
float refVoltage = 3247.0;        // ADC reference voltage in mV (as measured by multimeter)
float dvdt = .021992;             // Seebeck coefficient for a K-type probe (mV/deg F)
float opAmpGain0 = 100.0/0.991;
float opAmpGain1 = 100.0/0.982;

void setup() {
//  analogReference(INTERNAL);
  analogReference(EXTERNAL);      // set reference to ~3.3V
  Serial.begin(9600);
}

void loop() {
  val0 = analogRead(sensor0);
  val1 = analogRead(sensor1);
  
  mv0 = (val0/pow(2,adcBitDepth))*refVoltage/opAmpGain0;          // voltage output by thermocouple
  mv1 = (val1/pow(2,adcBitDepth))*refVoltage/opAmpGain1;
  
  temp0 = ambTemp + mv0/dvdt;     // calculate temp from Seebeck effect
  temp1 = ambTemp + mv1/dvdt;
  temp0c = (5.0/9.0)*(temp0-32);

  Serial.print("Temp @ probe 0 = ");
  Serial.print(temp0);
  Serial.println("* F");
  
  Serial.print("Temp @ probe 1 = ");
  Serial.print(temp1);
  Serial.println("* F");
  delay(500);
}
