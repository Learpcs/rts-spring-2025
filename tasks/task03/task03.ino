volatile unsigned long previousMicros = 0;
volatile unsigned long totalInterval = 0;
volatile unsigned long totalSquaredInterval = 0;
volatile unsigned int sampleCount = 0;
const unsigned int maxSampleSize = 1000;

void setup() {
  Serial.begin(115200);
  pinMode(21, INPUT);
  attachInterrupt(digitalPinToInterrupt(21), recordInterval, CHANGE);
}

void loop() {
  if (sampleCount >= maxSampleSize) {
    noInterrupts();
    unsigned long sumIntervals = totalInterval;
    unsigned long sumSquaredIntervals = totalSquaredInterval;
    unsigned int totalSamples = sampleCount;
    totalInterval = 0;
    totalSquaredInterval = 0;
    sampleCount = 0;
    interrupts();

    unsigned long average = sumIntervals / totalSamples;
    unsigned long variance = (sumSquaredIntervals / totalSamples) - (average * average);
    unsigned long standardDeviation = sqrt(variance);

    Serial.print("Average: ");
    Serial.print(average);
    Serial.print(" us, Total Squared: ");
    Serial.print(sumSquaredIntervals);
    Serial.print(" us, Total Samples: ");
    Serial.print(totalSamples);
    Serial.print(" us, Average^2: ");
    Serial.print(average * average);
    Serial.print(" us, Variance: ");
    Serial.print(variance);
    Serial.print(" us, StdDev: ");
    Serial.print(standardDeviation);
    Serial.println(" us");
  }
}

void recordInterval() {
  unsigned long currentMicros = micros();
  if (previousMicros) {
    unsigned long interval = currentMicros - previousMicros;

    totalInterval += interval;
    totalSquaredInterval += interval * interval;
    sampleCount++;
  }

  previousMicros = currentMicros;
}
