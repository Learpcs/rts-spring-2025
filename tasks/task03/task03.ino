volatile unsigned long long previousMicros = 0;
volatile unsigned long long totalInterval = 0;
volatile unsigned long long totalSquaredInterval = 0;
volatile unsigned long long sampleCount = 0;
const unsigned long long maxSampleSize = 1000;

void setup() {
  Serial.begin(9600);
  pinMode(3, INPUT);
  attachInterrupt(digitalPinToInterrupt(3), recordInterval, HIGH);
 }

void loop() {
  if (sampleCount >= maxSampleSize) {
    noInterrupts();
    unsigned long long sumIntervals = totalInterval;
    unsigned long long sumSquaredIntervals = totalSquaredInterval;
    unsigned long long totalSamples = sampleCount;
    totalInterval = 0;
    totalSquaredInterval = 0;
    sampleCount = 0;   
    interrupts();
   

    float average = sumIntervals / totalSamples;
    float variance = (sumSquaredIntervals / totalSamples) - (average * average);
    unsigned long long standardDeviation = sqrt(variance);

    Serial.print("Average: ");
    Serial.print((float)average);
    Serial.print(" us, StdDev: ");
    Serial.print((float)standardDeviation);
    Serial.println(" us");

  }
}

void recordInterval() {
  unsigned long long currentMicros = micros();
  unsigned long long interval = currentMicros - previousMicros;

  totalInterval += interval;
  totalSquaredInterval += interval * interval;
  sampleCount++;

  previousMicros = currentMicros;
}
