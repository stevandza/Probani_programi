
//Quadrature signal generator two outputs offset 90 degrees
//emulate rotary encoder
//Timer 1 CTC with ICR1 TOP and

void setup() {

  pinMode(9, OUTPUT); //output A
  pinMode(10, OUTPUT); //output B

  TCCR1A = 0; //clear timer registers
  TCCR1B = 0;
  TCNT1 = 0;
  GTCCR |= 1 << PSRASY; //reset prescaler

  //ICR1 and Prescaler sets frequency
  //no prescaler .0625 us per count @ 16mhz
  //prescaler 8 .5 us per count

 // TCCR1B |=  _BV(CS11); // prescaler 8
  TCCR1B |= _BV(CS10); //no prescaler

  //counts are zero indexed 2edges per ICR1 period
  //numerical values for prescaler 8.
  //e.g. 10k period give 20k encoder counts

  ICR1 = 19;//10k ICR1 period  20k encoder counts
  //ICR1 = 99; //20k ICR1 period 40k encoder counts
  //ICR1 = 49; //40K ICR1 period 80k encoder counts
  //ICR1 = 46; //42.5K ICR1 period 85k encoder counts
  //ICR1 = 41; //47.5k ICR1 period 95K encoder counts
  //ICR1 = 39; //50k ICR1 period 100k encoder counts
  //ICR1 = 29; //66.6K ICR1 period 133k encoder counts
  //ICR1 = 19; //100k ICR1 period 200k encoder counts
  
  OCR1A = ICR1 - 1; //two different pulse widths almost 100% duty cycle
  OCR1B = OCR1A / 2; //offset by half period

  TCCR1B |= _BV(WGM13) | _BV(WGM12); //CTC mode with ICR1
  TCCR1A = _BV(COM1A0) | _BV(COM1B0); //Toggle OC1A/OC1B on compare match
}
void loop () {}
