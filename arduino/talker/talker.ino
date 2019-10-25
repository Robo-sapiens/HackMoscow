const byte num_chars = 32;
byte received_chars[num_chars];

boolean new_data = false;

void setup() {
    Serial.begin(9600);
    Serial.println("<Arduino is ready>");
}

void loop() {
    recv();
    parse_new_data();
}

void recv() {
    static boolean recv_in_progress = false;
    static byte ndx = 0;
    char start_marker = '<';
    char end_marker = '>';
    byte rc;
 
    if (new_data) {
        return;
    }
    while (Serial.available() > 0) {
        rc = Serial.read();

        if (recv_in_progress) {
            if (rc != end_marker) {
                received_chars[ndx] = rc;
                ndx++;
                if (ndx >= num_chars) {
                    ndx = num_chars - 1;
                }
            } else {
                received_chars[ndx] = '\0'; // terminate the string
                recv_in_progress = false;
                ndx = 0;
                new_data = true;
            }
        } else if (rc == start_marker) {
            recv_in_progress = true;
        }
    }
}

void parse_new_data() {
    if (!new_data) {
        return;
    }
    for (int i = 0; i < 3; ++i) {
        Serial.println(received_chars[i]);
    }
    new_data = false;
}
