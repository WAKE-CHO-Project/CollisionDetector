

// unsigned char waveToggle = 0x00;
// unsigned char pulseCount = 0;


// Echo Pin
#define ECHO_PIN 4

// Trigger Pin
#define TRIGGER_PIN 5

#define BUZZER_PIN 3
#define LED_PIN 13

#define DISTANCE_TO_BEEP 100
 



 DeclareTaskLoop(Blinker);
 DeclareTaskLoop(DistanceMeter);
 DeclareTaskLoop(SerialPrinter);


double duration = 0.0;
double distance = 0.0;

void setup() { 
    pinMode(ECHO_PIN, INPUT);
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);

    Serial.begin(19200);


    CreateTaskLoop(Blinker, LOW_PRIORITY);
    CreateTaskLoop(DistanceMeter, LOW_PRIORITY);
    CreateTaskLoop(SerialPrinter, LOW_PRIORITY);
    
    Serial.println("Start");

    // tone(3, 880);

    // DDRD  |=  B00001000;


    // TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20); // 高速PWM

    // TCCR2B = _BV(CS21) |_BV(CS20) | _BV(WGM22);    // 分周1/64

    // OCR2A = 63;
    // OCR2B = 0;

    // //タイマー割り込み開始
    // //TIMSK2 |= _BV(TOIE2);

    // tone(3, 4000);
}

void loop(){
    
}

TaskLoop(SerialPrinter){
    Serial.print("Distance:");
    Serial.print(distance);
    Serial.println(" cm");
    TaskDelay(500);
}

TaskLoop(DistanceMeter) {
    digitalWrite(TRIGGER_PIN, LOW); 
    delayMicroseconds(2); 
    digitalWrite(TRIGGER_PIN, HIGH ); //超音波を出力
    delayMicroseconds( 10 ); //
    digitalWrite( TRIGGER_PIN, LOW );
    duration = pulseIn( ECHO_PIN, HIGH ); //センサからの入力
    if (duration > 0) {
        duration = duration/2; //往復距離を半分にする
        distance = duration*340*100/1000000; // 音速を340m/sに設定
        

        if(distance < DISTANCE_TO_BEEP){
            tone(BUZZER_PIN, 4000);
        }
        else{
            noTone(BUZZER_PIN);
        }
    }
    //delay(500);
}




TaskLoop(Blinker){

    TaskDelay(1000);
    digitalWrite(LED_PIN, HIGH);
    TaskDelay(1000);
    digitalWrite(LED_PIN, LOW);
}











// ### 過去の遺産 でも残す ###########################################
// ISR(TIMER2_OVF_vect){
 
//     // // High
//     // if(waveToggle){
//     //     waveToggle ^= 0x01;


//     //     OCR2A = 6;
//     //     OCR2B = 2;
//     // }

//     // // Low
//     // else {
//     //     pulseCount++;
//     //     if(pulseCount > 10){
//     //         pulseCount = 0;
            
                    
//     //         OCR2A = 63;
//     //         OCR2B = 63;

//     //         waveToggle ^= 0x01;
//     //     }
//     // }

// }

// ISR(TIMER2_COMPB_vect) {

// }
