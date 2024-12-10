#include <Arduino.h>

const int dacPin = 25;

void Triangle(float amplitude, float period, float symmetry, int ciclo);

void setup() {
  pinMode(dacPin, OUTPUT);
}

void loop() {
  Triangle(80,1.0,0.5, 10);
  Triangle(160,1.0,0.5, 10);
  Triangle(240,1.0,0.5, 10);
}

void Triangle(float amplitude, float period, float symmetry, int ciclo) {
 
    if (symmetry < 0.0 || symmetry > 1.0) symmetry = 0.5; 
    if (amplitude < 0.0 || amplitude > 255.0) amplitude = 255.0;

    short count = 0;

    unsigned long ascendente = symmetry * 255;     // Puntos en la rampa ascendente
    unsigned long descendente = (1.0 - symmetry) * 255; // Puntos en la rampa descendente
    unsigned long total = ascendente + descendente;

    unsigned long dt = period/ (2 * total); // Tiempo entre pasos (en ms)

    while(true){
        // Rampa ascendente
        for (int i = 0; i < ascendente; i++) {
            int value = (amplitude / ascendente) * i; // Calcular el valor actual
            dacWrite(dacPin, value);              // Escribir en el DAC
            delayMicroseconds(dt * 1000);         // Esperar
        }
        // Rampa descendente
        for (int i = 0; i < descendente; i++) {
            int value = amplitude - ((amplitude / descendente) * i); // Calcular el valor actual
            dacWrite(dacPin, value);                              // Escribir en el DAC
            delayMicroseconds(dt * 1000);                         // Esperar
        }

        if(ciclo < count)
          break;
        count++;
    }
}
