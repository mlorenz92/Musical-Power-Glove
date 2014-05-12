//importing minim and serial input
import processing.serial.*;
import ddf.minim.*;
import ddf.minim.ugens.*;

//defining key variables
Serial port;
Minim minim;
AudioOutput out;

//lastTime is used in our function as a way to incorporate
//a delay into draw
long lastTime = 0;

//defining notes
int sound1;
int sound2;
int sound3;
int sound4;
int sound5;

void setup() {
  //setting up the "handshake" between processing and the arduino
  println(Serial.list());
  String portName = Serial.list()[5];
  port = new Serial(this, portName, 9600);
  port.write(65);
  //creating minim
  minim = new Minim(this);
  out = minim.getLineOut();
  out.setGain(20);
  
  lastTime = millis();

}
void draw() {
  //while we can read in values go for it
  while(port.available() >0){
    //read in the input
    String input = port.readStringUntil('*');
    //if the input is available, and most importantly
    //if it has been more than .25 of a second since the lastTime
    //this allows for enough time for minim to play the notes
    if(input != null && millis()-lastTime > 250){
      println(input);
      int [] vals = int(splitTokens(input, ",*"));
      try {
        //read in the values into their respective variables
        out.pauseNotes();
        sound1 = vals[1];
        sound2 = vals[2];
        sound3 = vals[3];
        sound4 = vals[4];
        sound5 = vals[5];
        //and check if any of the notes are supposed to be playing
        //if so play them
        if(sound1 > 0){
          out.playNote(0, 0.25, "C5");
          out.playNote(0, 0.25, "A5");
          out.playNote(0, 0.25, "E5");
        }
        if(sound2 > 0){
          out.playNote(0, 0.25,"C5");
          out.playNote(0, 0.25, "F5");
          out.playNote(0, 0.25, "A5");
        }
        if(sound3 > 0){
          out.playNote(0, 0.25,"C5");
          out.playNote(0, 0.25, "A5");
          out.playNote(0, 0.25, "G5");
        }
        if(sound4 > 0){
          out.playNote(0, 0.25,"B5");
          out.playNote(0, 0.25, "D5");
          out.playNote(0, 0.25, "G5");
        }
        if(sound5 > 0){
          out.playNote(0, 0.25,"A5");
        }
        //play notes
        out.resumeNotes();
      //catch any exceptions
      }catch (ArrayIndexOutOfBoundsException e){
        println(e);
      }catch (NullPointerException e) {
        println(e);
      }catch (Exception e) {
        println(e);
      }
      //restart lastTime after we have played the notes
      lastTime = millis();
    }
  }
}
