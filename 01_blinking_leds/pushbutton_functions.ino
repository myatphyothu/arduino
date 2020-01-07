
// call during loop
void registerBtnPress(){
  int pushBtnState = digitalRead(buttonInPIN);
  if (low) {
    if (pushBtnState == HIGH) {
      low = false;
      btnPressTime = millis();
    }
  } else {

    if (pushBtnState == HIGH) {
      if (millis() - btnPressTime > timeToWaitBeforeNextPress){
        low = true;
      }
    }else{
      low = true;
      BTN_PRESSED = !BTN_PRESSED;
    }
  }
}
