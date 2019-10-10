

// Get Serial Data from an Arduino
// Parse it with a separator caracter ","
 
// import the Processing serial library
import processing.serial.*;    
import http.requests.*;
import cc.arduino.*;

Serial myPort; // The serial port



PFont f;
JSONObject json;
String message = "";
boolean isReturn = false;
 
 
void setup() {
  size(640,480);
  // Open serial port
  //printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[9], 9600);
 
  // Read bytes into a buffer until you get a linefeed (ASCII 10):
  myPort.bufferUntil('\n');
 
  //draw with smooth edges:
  //smooth();
  
  f = createFont("Arial",16); // STEP 2 Create Font




}
 
void draw() {
  if(isReturn) {
  
  background(255);

  textFont(f,16);
  fill(0);
  text(message,0,100);   // STEP 5 Display Text

  isReturn = false;
  }

}
 
// serialEvent  method is run automatically by the Processing applet
// whenever the buffer reaches the byte value set in the bufferUntil()
// method in the setup():
void serialEvent(Serial myPort) {
  GetRequest get = new GetRequest("https://api.forismatic.com/api/1.0/?method=getQuote&format=json&lang=en&json=?");
  get.send();
  JSONObject json = parseJSONObject(get.getContent());
    if (json == null) {
      println("JSONObject could not be parsed");
    } else {  
      println(json);
      message = json.getString("quoteText");
      isReturn = true;
    }
  // read the serial buffer:
  String myString = myPort.readStringUntil('\n');
  println(myString);
}
