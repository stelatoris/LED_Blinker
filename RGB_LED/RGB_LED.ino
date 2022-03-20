const int gear_redPin= 7;
const int gear_greenPin = 6;
const int gear_bluePin = 5;
const int gear_swtch = 2;
int gear_swtch_st{0};

class LED_timer {
  public:
    LED_timer() : prev_time{0} {}

    bool blink_LED( int on, int off, long total);
    void end();

    
    int on_time;
    int off_time;
    long total_interval;
    
    long prev_on_time;
    long prev_off_time;
    long prev_time;
    
    bool blink_on{false};
    bool on_interval;
    bool off_interval;
    bool switch_ON;
    bool sequence_done=false;
};

void LED_timer::end()
{
  prev_on_time=0;
  prev_off_time=0;
  prev_time=0;

  blink_on=false;
  on_interval=false;
  off_interval=false;
  switch_ON=false;
  sequence_done=false;
}

bool LED_timer::blink_LED( int on_int, int off_int, long total)
{
  total_interval=total;
  on_time=on_int;
  off_time=off_int;

  if(sequence_done) return false;
  
  if(!blink_on && !sequence_done) {   // Start here
      blink_on=true;
      prev_on_time=millis();
      prev_time=millis();
      on_interval=true;    
      }
  else {
    if(millis()-prev_time>total_interval) {
    sequence_done=true;
    blink_on=false;
    on_interval=false;
    off_interval=false;
    sequence_done=true;
    return false;
    }
    else{
      if(blink_on) {
        if(on_interval) {
          if(millis()-prev_on_time>on_time) {
            on_interval=false;
            off_interval=true;
            prev_off_time=millis();
            return false;        
          }
          return true;
        }
        else{
          if(millis()-prev_off_time>off_time){
            off_interval=false;
            on_interval=true;
            prev_on_time=millis();
            return true;
          }
          return false;
        }
      }
      else return false;
    }
  }
  
  
  
  /*
  Serial.print("\t total_interval:");
  Serial.print(total_interval);
  Serial.print("\t millis()-prev_time:");
  Serial.print(millis()-prev_time);
  Serial.print("\t prev_time:");
  Serial.print(prev_time);
  Serial.print("\t millis()-prev_on_time:");
  Serial.print(millis()-prev_on_time);
  Serial.print("\t prev_on_time:");
  Serial.print(prev_on_time);
  Serial.print("\t millis()-prev_off_time:");
  Serial.print(millis()-prev_off_time);
  Serial.print("\t prev_off_time:");
  Serial.print(prev_off_time);


  Serial.print("\t blink_on:");
  Serial.print(blink_on);
  Serial.print("\t on_interval:");
  Serial.print(on_interval);
  Serial.print("\t off_interval:");
  Serial.print(off_interval);

  bool status_LED;

    if(sequence_done==true) {
      return false;
    }
    else if(sequence_done==false) {  // Binking sequence is already ON
      if(millis()-prev_time>total_interval) { //if total interval had passed
        sequence_done=true;
        Serial.print("\t timer total :");
        Serial.print(millis()-prev_time);
        blink_on=false;
        on_interval=false;
        off_interval=false;
        //Serial.print("\t LED OFF at total interv:");
        //Serial.print(false);
        status_LED=false;           // ENDS sequence : LED turns OFF
      }
      else {
        if(on_interval==true){
          if(millis()-prev_on_time>on_time) { // if ON intervall had passed
            on_interval=false;
            prev_off_time=millis();
            off_interval=true;
            //Serial.print("\t LED OFF at ON interv:");
            //Serial.print(false);
            status_LED=false;         // LED turns OFF
            Serial.print("\t HERE:");
        
          }
          else {
            //Serial.print("\t LED ON at ON interv:");
            //Serial.print(true);
            off_interval=false;
            status_LED=true;     // LED stays ON
          }
        }
        if(off_interval) {
          if(millis()-prev_off_time>off_time) { // if OFF intervall had passed
            off_interval=false;
            on_interval=true;
            //Serial.print("\t LED ON at OFF interv:");
            //Serial.print(true);
            //return true;        // LED turns ON
          }
          else status_LED=false;    // LED stays OFF
        }  
       }
    }
    else {          // Begin blinking sequence
      blink_on=true;
      on_interval=true;
      prev_time=millis();
      prev_on_time=millis();
      Serial.print("\t Blink Begin!");
    }
  
    return status_LED;  
    */   
}

struct LED {
  
  LED(int p) : pin{p}, t{LED_timer()} {}
  int pin;
  LED_timer t;
};

//--------------------------------------------------------------
LED_timer gear_up;
LED_timer gear_down;

void setColor(int redValue, int greenValue, int blueValue) 
{
  analogWrite(gear_redPin, redValue);
  analogWrite(gear_greenPin, greenValue);
  analogWrite(gear_bluePin, blueValue);
}

void gears_panel()
{
  
  gear_swtch_st=digitalRead(gear_swtch);
  if (gear_swtch_st) {      // Gears DOWN
    gear_up.end();
    if(!gear_down.sequence_done){
      if(gear_down.blink_LED(700, 700, 7700)) {
        setColor(0, 255, 0);
      }
      else {
        setColor(0, 0, 0);
      }
    }
    else {
        setColor(0, 255, 0);
      }    
    //gear_up.switch_ON=false;
  }
  else {    // Gears UP
    gear_down.end();
    if(gear_up.blink_LED(700, 700, 7700)) {
      setColor(255, 0, 0);
    }
    else {
      setColor(0, 0, 0);
    }   
  }
  Serial.println(" ");
}

void setup() {
  Serial.begin(9600);
  
  pinMode(gear_redPin, OUTPUT);
  pinMode(gear_greenPin, OUTPUT);
  pinMode(gear_bluePin, OUTPUT);
  pinMode(gear_swtch, INPUT);

  
}

void loop() {
  gears_panel();
}
