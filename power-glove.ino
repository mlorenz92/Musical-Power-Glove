//defining all the pins
const int flexPin1 = A0;
const int flexPin2 = A1;
const int flexPin3 = A2;
const int flexPin4 = A3;
const int flexPin5 = A4;
//defining the array size for the baseline algorithm
const int arraySize = 50;
boolean firstRun = true;

//all necessary variables
int flex1[arraySize];
int flex2[arraySize];
int flex3[arraySize];
int flex4[arraySize];
int flex5[arraySize];
int baselineFlex1;
int baselineFlex2;
int baselineFlex3;
int baselineFlex4;
int baselineFlex5;

void setup(){
  Serial.begin(9600);
}

void loop(){
  //if this is the fisrt run, run the algorithm
  //to find a baseline value used to calculate the delta
  if(firstRun){
    firstRun=false;
    //read in all the values for each finger and put them into their own array
    for(int i =0; i< arraySize; i++){
      int sound1 = analogRead(flexPin1);
      int sound2 = analogRead(flexPin2);
      int sound3 = analogRead(flexPin3);
      int sound4 = analogRead(flexPin4);
      int sound5 = analogRead(flexPin5);
      flex1[i] = sound1;
      flex2[i] = sound2;
      flex3[i] = sound3;
      flex4[i] = sound4;
      flex5[i] = sound5;
    }
    //once done sequence through each array calculating the average for
    //those fingers
    int flex1Average = 0;
    int flex2Average = 0;
    int flex3Average = 0;
    int flex4Average = 0;
    int flex5Average = 0;
    for(int i=0; i<arraySize; i++){
      flex1Average = flex1Average + flex1[i];
      flex2Average = flex2Average + flex2[i];
      flex3Average = flex3Average + flex3[i];
      flex4Average = flex4Average + flex4[i];
      flex5Average = flex5Average + flex5[i];
    }
    //calculate the average
    baselineFlex1 = flex1Average/arraySize;
    baselineFlex2 = flex2Average/arraySize;
    baselineFlex3 = flex3Average/arraySize;
    baselineFlex4 = flex4Average/arraySize;
    baselineFlex5 = flex5Average/arraySize;
  }
  //then at each subsequent iteration read in the values from the fingers
  //and calcualte the delat from the average
  int sound1 = analogRead(flexPin1);
  sound1 = baselineFlex1 - sound1;
  int sound2 = analogRead(flexPin2);
  sound2 = baselineFlex2 - sound2;
  int sound3 = analogRead(flexPin3);
  sound3 = baselineFlex3 - sound3;
  int sound4 = analogRead(flexPin4);
  sound4 = baselineFlex4 - sound4;
  int sound5 = analogRead(flexPin5);
  sound5 = baselineFlex5 - sound5;
  
  //send the values out to processing
  Serial.println((String)0 + "," + (String)sound1 + "," + (String)sound2 + "," + (String)sound3  + "," + (String)sound4  + "," + (String)sound5 + "*");
  delay(20);
}
