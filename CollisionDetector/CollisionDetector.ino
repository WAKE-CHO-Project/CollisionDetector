

unsigned char waveToggle = 0x00;
unsigned char pulseCount = 0;




void setup() { 
    pinMode(4, OUTPUT);

    Serial.begin(19200);
    
    Serial.println("Start");

    // tone(3, 880);

    DDRD  |=  B00001000;


    TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20); // 高速PWM

    TCCR2B = _BV(CS21) |_BV(CS20) | _BV(WGM22);    // 分周1/64

    OCR2A = 63;
    OCR2B = 0;

    //タイマー割り込み開始
    TIMSK2 |= _BV(TOIE2);


}

void loop() {

    // digitalWrite(4, LOW);
    // delay(1000);

    
    // digitalWrite(4, HIGH);
    //delay(1000);

    Serial.println(waveToggle);
}

ISR(TIMER2_OVF_vect){

    // High
    if(waveToggle){
        waveToggle ^= 0x01;


        OCR2A = 6;
        OCR2B = 2;
    }

    // Low
    else {
        pulseCount++;
        if(pulseCount > 10){
            pulseCount = 0;
            
                    
            OCR2A = 63;
            OCR2B = 63;

            waveToggle ^= 0x01;
        }
    }

}

ISR(TIMER2_COMPB_vect) {

}
