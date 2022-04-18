#include <Arduino.h>
#include <SevSegCounter.hpp>

namespace TrafficLights {
    enum States: int { RED, YELLOW, GREEN };

    // Classe responsável por armazenar todos os pinos.
    class Pins {
        public: // vars
            const uint8_t pin_array[5];
            const bool has_ped_lights;

            const uint8_t& light_red;
            const uint8_t& light_yellow;
            const uint8_t& light_green;

            const uint8_t& pe_light_red;
            const uint8_t& pe_light_green;

        public: // funcs
            Pins(
                uint8_t light_red,
                uint8_t light_yellow,
                uint8_t light_green
            );

            Pins(
                uint8_t light_red,
                uint8_t light_yellow,
                uint8_t light_green,
                uint8_t pe_light_red,
                uint8_t pe_light_green
            );
    };

    /**
     * Classe responsável pelo controle (não lógica) do semáforo.
     *
     * Aceita o funcionamento apenas das luzes básicas, sendo o semáforo de
     * pedestres opcional.
     */
    class Controller {
        private: // vars
            const Pins& light_pins;
            const uint64_t yellow_light_threshold = 20; // in percents
            States actual_state = RED;

        public: // funcs
            explicit
            Controller(Pins& light_pins);

            Controller(Pins& light_pins, uint64_t yellow_light_threshold);

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
            void startTimer(uint64_t red_delay_ms, uint64_t green_delay_ms);

            States get_actual_state();

        private: // funcs
            /**
             * Função de início. Feito para reduzir código.
             */
            void setup();

            /**
             * Muda o estado do semáforo.
             * 
             * @param state: estado ao qual o semáforo será modificado.
             */
            void change_to_state(States state);

            /**
             * Desliga todas as luzes primárias e de pedestre
             */
            void clear_lights();
    };
} // namespace TrafficLights
