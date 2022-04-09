#include <Arduino.h>

#include <LightPins.cpp>

/**
 * Classe responsável pelo controle (não lógica) do semáforo.
 *
 * Aceita o funcionamento apenas das luzes básicas, sendo o semáforo de
 * pedestres opcional.
 */
class TrafficLights {
    public: // vars
        enum States: int { RED, YELLOW, GREEN };

    private: // vars
        const LightPins& light_pins;
        const uint64_t yellow_light_threshold = 20; // in percents
        States actual_state = RED;

    public: // funcs
        TrafficLights(LightPins& light_pins): light_pins(light_pins) {
            change_to_state(RED);
        }

        TrafficLights(LightPins& light_pins, uint64_t yellow_light_threshold):
            light_pins(light_pins),
            yellow_light_threshold(yellow_light_threshold)
        {
            change_to_state(RED);
        }

        /**
         * Realiza a temporização do sinal e troca de estados (luzes).
         * 
         * (yellow_light_threshold)% do sinal vermelho será o tempo do sinal
         * amarelo.
         * 
         * @param red_delay_ms: tempo em que o semáforo permanecerá na luz
         * vermelha após o acionamento da função.
         * @param green_delay_ms: tempo mínimo em que o semáforo permanecerá na
         * luz verde antes de sair da função.
         */
        void startTimer(uint64_t red_delay_ms, uint64_t green_delay_ms) {
            uint64_t yellow_wait = yellow_light_threshold * red_delay_ms / 100ul;
            uint64_t red_wait = red_delay_ms - yellow_wait;

            change_to_state(RED);
            delay(red_wait);

            change_to_state(YELLOW);
            delay(yellow_wait);

            change_to_state(GREEN);
            delay(green_delay_ms);
        }

        /**
         * Finaliza o semáforo voltando ao sinal vermelho.
         */
        void restart() {
            change_to_state(RED);
        }

        States get_actual_state() {
            return actual_state;
        }

    private: // funcs
        /**
         * Muda o estado do semáforo.
         * 
         * @param state: estado ao qual o semáforo será modificado.
         */
        void change_to_state(States state) {
            // 1. Define novo estado;
            actual_state = state;

            // 2. Apaga as luzes;
            clear_lights();

            /**
             * 3. Liga apenas as luzes pertencentes ao estado.
             * 
             * |   Luzes   | Luzes de |
             * | Primárias | Pedestre |
             * |-----------|----------|
             * |  Vermelha | Verde    |
             * |   Amarela | Vermelha |
             * |     Verde | Vermelha |
             */
            switch (state) {
                case States::RED:
                    digitalWrite(light_pins.light_red, HIGH);
                    if (light_pins.has_ped_lights) {
                        digitalWrite(light_pins.pe_light_green, HIGH);
                    }
                    break;
                
                case States::YELLOW:
                    digitalWrite(light_pins.light_yellow, HIGH);
                    if (light_pins.has_ped_lights) {
                        digitalWrite(light_pins.pe_light_red, HIGH);
                    }
                    break;
                
                case States::GREEN:
                    digitalWrite(light_pins.light_green, HIGH);
                    if (light_pins.has_ped_lights) {
                        digitalWrite(light_pins.pe_light_red, HIGH);
                    }
                    break;
                
                default:
                    break;
            }
        }

        // Desliga todas as luzes primárias e de pedestre
        void clear_lights() {
            uint8_t scan_range = 3;

            if (light_pins.has_ped_lights) {
                // Se as luzes de pedestre estiverem inclusas, adiciona
                // 'pe_light_red' e 'pe_light_green' ao range do for.
                scan_range += 2;
            }

            // Percorre toda a lista definindo cada pino como LOW. Incluindo os
            // pinos das luzes de pedestre caso a condicional anterior seja
            // verdadeira.
            for (uint8_t i = 0; i < scan_range; i++) {
                digitalWrite(light_pins.pin_array[i], LOW);
            }
        }
};
