#include <Arduino.h>
#include <SevSeg.h>

namespace SevSegCounter {
    enum DisplayTypes : uint8_t { COMM_CATHODE, COMM_ANODE };

    class Pins {
        public: // vars
            const uint8_t pin_array[7];

            const uint8_t& pin_A;
            const uint8_t& pin_B;
            const uint8_t& pin_C;
            const uint8_t& pin_D;
            const uint8_t& pin_E;
            const uint8_t& pin_F;
            const uint8_t& pin_G;

        public: // funcs
            Pins(
                uint8_t pin_A,
                uint8_t pin_B,
                uint8_t pin_C,
                uint8_t pin_D,
                uint8_t pin_E,
                uint8_t pin_F,
                uint8_t pin_G
            );
    };

    class Controller {
        public: // vars
            const DisplayTypes display_type;

        private: // vars
            SevSeg display;
            const Pins& sevseg_pins;


        public: // funcs
            /**
             * @param display_type: Tipo de display (Catodo ou Anodo comum).
             * @param sevseg_pins:  Objeto contendo os pinos para controle do
             * display.
             */
            Controller(DisplayTypes display_type, Pins& sevseg_pins);

            /**
             * Realiza do delay necessário exibindo o progresso (segundos) no
             * display de 7 seguimentos.
             * 
             * Aceita contagens crescentes e decrescentes.
             * Exemplos:
             * ```cpp
             * delay(0, 5); // Contagem de 0 a 5 segundos.
             * delay(8, 0); // Contagem de 8 a 0 segundos.
             * delay(3, 8); // Contagem de 3 a 8 segundos.
             * delay(6, 5); // Contagem de 6 a 5 segundos.
             * ```
             * @param sec_start: Tempo de início em segundos.
             * @param sec_end:   Tempo de finalização em segundos.
             */
            void delay(uint8_t sec_start, uint8_t sec_end);


        private: // funcs
            /**
             * Encerra o fluxo do timer colocando um "-" no display.
             */
            void end();
    };
} // namespace SevSegCounter
