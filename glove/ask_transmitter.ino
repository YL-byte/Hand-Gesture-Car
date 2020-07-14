
void trans_setup() {
  driver.init();
}

//int trans_loop(angle_pitch_acc, angle_roll_acc) {
//    const char *msg = angle_pitch_acc << sizeof(angle_pitch_acc)||angle_roll_acc;
//
//    driver.send((uint8_t *)msg, strlen(msg));
//    driver.waitPacketSent();
//    delay(200);
//}
