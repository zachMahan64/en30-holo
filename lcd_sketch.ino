void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial to be ready
  }
  delay(500); // let serial montior connect
}

void loop() {
  // put your main code here, to run repeatedly:
  tester();
  delay(1000);
}

void print_lcd_arr(int* arr, size_t rows, size_t cols) {
    for (int i = 0; i < rows; i++) {
        for (int k = 0; k < cols; k++) {
            Serial.print(arr[cols * i + k]);
        }
        Serial.println();
    }
    Serial.println("\n\n\n\n\n\n\n\n");
}

void tester() {
    constexpr int rows = 2;
    constexpr int cols = 16;
    int my_arr[rows][cols] = {0};

    print_lcd_arr((int*)my_arr, rows, cols);
}