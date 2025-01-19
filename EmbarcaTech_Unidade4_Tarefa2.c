#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Definições das portas GPIO dos LEDs
#define GREEN_LED_PIN 11
#define BLUE_LED_PIN 12
#define RED_LED_PIN 13

//Definição da porta GGPIO do BUZZER
#define BUZZER_PIN 21

// Frequências das notas musicais (em Hz)
enum NotasMusicais {
    DO = 2640, // Dó
    RE = 2970, // Ré
    MI = 3300, // Mi
    FA = 3520, // Fá
    SOL = 3960, // Sol
    LA = 4400, // Lá
    SI = 4950  // Si
};

// Inicializa LEDs e Buzzer
void init_leds_and_buzzer() {
    
    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);
    gpio_put(GREEN_LED_PIN, 0);

    gpio_init(BLUE_LED_PIN);
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);
    gpio_put(BLUE_LED_PIN, 0);

    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
    gpio_put(RED_LED_PIN, 0);

    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    gpio_put(BUZZER_PIN, 0);
}

// Configura o PWM no pino do buzzer com uma frequência especificada
void set_buzzer_frequency(uint pin, uint frequency) {
    // Obter o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configurar o pino como saída de PWM
    gpio_set_function(pin, GPIO_FUNC_PWM);

    // Configurar o PWM com frequência desejada
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (frequency * 4096)); // Calcula divisor do clock

    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(pin, 0); // Inicializa com duty cycle 0 (sem som)
}

// Função para tocar o buzzer por um tempo especificado (em milissegundos)
void play_buzzer(uint pin, uint frequency, uint duration_ms) {

    set_buzzer_frequency(pin, frequency);   
    pwm_set_gpio_level(pin, 32768);           
    sleep_ms(duration_ms);                   
    pwm_set_gpio_level(pin, 0);              
}

// Função para tocar a nota Dó
void playDo(uint duration_ms) {
    gpio_put(GREEN_LED_PIN, 1); // Acende LED verde
    play_buzzer(BUZZER_PIN, DO, duration_ms);
    gpio_put(GREEN_LED_PIN, 0); // Apaga LED verde
}

// Função para tocar a nota Ré
void playRe(uint duration_ms) {
    gpio_put(BLUE_LED_PIN, 1); // Acende LED azul
    play_buzzer(BUZZER_PIN, RE, duration_ms);
    gpio_put(BLUE_LED_PIN, 0); // Apaga LED azul
}

void playMi(uint duration_ms){
    gpio_put(RED_LED_PIN, 1); //Acende LED vermelho
    play_buzzer(BUZZER_PIN,MI,duration_ms);
    gpio_put(RED_LED_PIN, 0); //Apaga LED vermelho
}

void playFa(uint duration_ms){
    gpio_put(GREEN_LED_PIN, 1); // Acende LED verde
    gpio_put(BLUE_LED_PIN, 1); // Acende LED azul
    play_buzzer(BUZZER_PIN,FA,duration_ms);
    gpio_put(GREEN_LED_PIN, 0); // Apaga LED verde
    gpio_put(BLUE_LED_PIN, 0); // Apaga LED azul
}

void playSol(uint duration_ms) {
    gpio_put(GREEN_LED_PIN, 1); // Acende LED verde
    gpio_put(RED_LED_PIN, 1); //Acende LED vermelho
    play_buzzer(BUZZER_PIN, SOL, duration_ms);
    gpio_put(GREEN_LED_PIN, 0); // Apaga LED verde
    gpio_put(RED_LED_PIN, 0); //Apaga LED vermelho
}

void playLa(uint duration_ms) {
    gpio_put(BLUE_LED_PIN, 1); // Acende LED azul
    gpio_put(RED_LED_PIN, 1); //Acende LED vermelho
    play_buzzer(BUZZER_PIN, LA, duration_ms);
    gpio_put(BLUE_LED_PIN, 0); // Apaga LED azul
    gpio_put(RED_LED_PIN, 0); //Apaga LED vermelho
}

void playSi(uint duration_ms) {
    gpio_put(GREEN_LED_PIN, 1); // Acende LED verde
    gpio_put(BLUE_LED_PIN, 1); // Acende LED azul
    gpio_put(RED_LED_PIN, 1); //Acende LED vermelho
    play_buzzer(BUZZER_PIN, SI, duration_ms);
    gpio_put(GREEN_LED_PIN, 0); // Apaga LED verde
    gpio_put(BLUE_LED_PIN, 0); // Apaga LED azul
    gpio_put(RED_LED_PIN, 0); //Apaga LED vermelho
}

void tocarDoReMi(){
    //Dó-Ré-Mi-Fá
    playDo(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playFa(300);
    sleep_ms(200);

    //Fá-Fá
    playFa(200);
    sleep_ms(300);
    playFa(200);
    sleep_ms(300);

    //Dó-Ré-Dó-Ré
    playDo(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);

    //Ré-Ré
    playRe(200);
    sleep_ms(300);
    playRe(200);
    sleep_ms(300);


    //Dó-Sol-Fa-Mi
    playDo(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);
    playFa(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);

    //Mi-Mi
    playMi(200);
    sleep_ms(300);
    playMi(200);
    sleep_ms(300);

    //Dó-Ré-Mi-Fá
    playDo(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playFa(300);
    sleep_ms(200);

    //Fá-Fá
    playFa(200);
    sleep_ms(300);
    playFa(200);
    sleep_ms(300);
}

void tocarParabens() {
    //DO-DO-RE-DO-SOL-FA-FA
    playDo(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);
    playFa(300);
    sleep_ms(200);
    playFa(300);
    sleep_ms(200);

    //DO-DO-RE-DO-SOL-FA
    playDo(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);
    playFa(300);
    sleep_ms(200);

    //LA-LA-DO-LA-FA-MI-RE
    playLa(300);
    sleep_ms(200);
    playLa(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(200);
    playLa(300);
    sleep_ms(200);
    playFa(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);

    //SI-SI-LA-FA-SOL-FA
    playSi(300);
    sleep_ms(200);
    playSi(300);
    sleep_ms(200);
    playLa(300);
    sleep_ms(200);
    playFa(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);
    playFa(300);
    sleep_ms(200);
}

// Função para tocar Cai Cai Balão
void tocarCaiCaiBalao() {
    // Sol Sol Mi Mi
    playSol(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);

    // Sol Sol Mi Mi
    playSol(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);

    // Sol Lá Sol
    playSol(300);
    sleep_ms(200);
    playLa(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);

    // Fá Mi Ré
    playFa(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);

    // Ré Mi Fá
    playRe(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playFa(300);
    sleep_ms(200);

    // Ré Mi Fá
    playRe(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playFa(300);
    sleep_ms(200);

    // Sol Lá Sol
    playSol(300);
    sleep_ms(200);
    playLa(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);

    // Fá Mi Ré
    playFa(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);

    // Dó
    playDo(600); // Última nota com maior duração
    sleep_ms(200);
}



void tocarJingleBells(){
    //Mi * 6
    for(int i = 0; i < 3; i++){
        playMi(300);
        sleep_ms(200);
    }
    sleep_ms(200);
    for(int i = 0; i < 3; i++){
        playMi(300);
        sleep_ms(200);
    }
    sleep_ms(200);

    //Mi-Sol-Do-Re-Mi
    playMi(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(400);

    //Fa-Fa-Fa-Fa
    for(int i = 0; i < 4; i++){
        playFa(300);
        sleep_ms(100);
    }
    sleep_ms(200);

    //Fa-Mi-Mi-Mi
    playFa(300);
    sleep_ms(200);
    for(int i = 0; i < 3; i++){
        playMi(300);
        sleep_ms(100);
    }
    sleep_ms(200);

    //Mi-Re-Re-Mi-Re-Sol
    playMi(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(400);

    //Mi * 6
    for(int i = 0; i < 3; i++){
        playMi(300);
        sleep_ms(200);
    }
    sleep_ms(200);
    for(int i = 0; i < 3; i++){
        playMi(300);
        sleep_ms(200);
    }
    sleep_ms(200);

    //Mi-Sol-Do-Re-Mi
    playMi(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(400);

    //Fa-Fa-Fa-Fa
    for(int i = 0; i < 4; i++){
        playFa(300);
        sleep_ms(100);
    }
    sleep_ms(200);

    //Fa-Mi-Mi-Mi
    playFa(300);
    sleep_ms(200);
    for(int i = 0; i < 3; i++){
        playMi(300);
        sleep_ms(100);
    }
    sleep_ms(200);

    //Re-Re-Sol-Sol-Do
    playSol(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(400);
}

void tocarBorboletinha(){
    //Sol-La-Sol-Do-Do
    playSol(300);
    sleep_ms(200);
    playLa(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);
    playSi(150);
    sleep_ms(100);
    playSi(150);
    sleep_ms(400);

    //Sol-La-Sol-Si-Si
    playSol(300);
    sleep_ms(200);
    playLa(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);
    playSi(150);
    sleep_ms(100);
    playSi(150);
    sleep_ms(400);

    //Sol-La-La-La-Sol-Si-Si
    playSol(300);
    sleep_ms(200);
    playLa(150);
    sleep_ms(100);
    playLa(150);
    sleep_ms(100);
    playLa(150);
    sleep_ms(100);
    playSol(150);
    sleep_ms(100);
    playSi(150);
    sleep_ms(100);
    playSi(150);
    sleep_ms(400);

    //Sol-La-Si-Do-Do
    playSol(300);
    sleep_ms(200);
    playLa(300);
    sleep_ms(200);
    playSi(300);
    sleep_ms(200);
    playSi(300);
    sleep_ms(200);
    playSi(300);
    sleep_ms(400);

    //Sol-La-Sol-Do
    playSol(300);
    sleep_ms(200);
    playLa(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);
    playSi(300);
    sleep_ms(400);

    //Sol-La-Sol-Si
    playSol(300);
    sleep_ms(200);
    playLa(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);
    playSi(300);
    sleep_ms(400);

    //Sol-La-La-La-Sol-Si-Si
    playSol(300);
    sleep_ms(200);
    playLa(150);
    sleep_ms(100);
    playLa(150);
    sleep_ms(100);
    playLa(150);
    sleep_ms(100);
    playSol(150);
    sleep_ms(100);
    playSi(150);
    sleep_ms(100);
    playSi(150);
    sleep_ms(400);

    //Sol-La-Si-Do-Sol-Do
    playSol(300);
    sleep_ms(200);
    playLa(300);
    sleep_ms(200);
    playSi(300);
    sleep_ms(200);
    playSi(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);
    playSi(300);
    sleep_ms(400);
}

void tocarPirulitoQueBateBate(){
    //Fa-Sol-La-La-La-Sol-Fa-Si-Si
    playFa(200);
    sleep_ms(100);
    playSol(200);
    sleep_ms(100);
    playLa(200);
    sleep_ms(100);
    playLa(200);
    sleep_ms(100);
    playLa(200);
    sleep_ms(200);
    playSol(200);
    sleep_ms(200);
    playFa(200);
    sleep_ms(200);
    playSi(200);
    sleep_ms(200);
    playSi(200);
    sleep_ms(400);

    //Mi-Fa-Sol-Sol-Sol-Fa-Mi-La
    playMi(200);
    sleep_ms(100);
    playFa(200);
    sleep_ms(100);
    playSol(200);
    sleep_ms(100);  
    playSol(200);
    sleep_ms(200);
    playSol(200);
    sleep_ms(100);
    playFa(200);
    sleep_ms(200);
    playMi(200);
    sleep_ms(200);
    playLa(200);
    sleep_ms(400);

    //Fa-Sol-La-La-La-Sol-Fa-Si-Re-Do-Si-La-Sol-Fa-Mi-Re
    playFa(200);
    sleep_ms(100);
    playSol(200);   
    sleep_ms(100);
    playLa(200);
    sleep_ms(100);
    playLa(200);
    sleep_ms(200);
    playLa(200);
    sleep_ms(100);
    playSol(200);
    sleep_ms(200);
    playFa(200);
    sleep_ms(200);
    playSi(200);
    sleep_ms(200);
    playRe(200);
    sleep_ms(200);
    playDo(200);
    sleep_ms(200);
    playSi(200);
    sleep_ms(200);
    playLa(200);
    sleep_ms(200);
    playSol(200);
    sleep_ms(200);
    playFa(200);
    sleep_ms(200);
    playMi(200);
    sleep_ms(200);
    playRe(200);
    sleep_ms(400);
}

void tocarNoiteFeliz(){
    playSol(900);
    sleep_ms(100);
    playLa(500);
    sleep_ms(100);
    playSol(900);
    sleep_ms(100);
    playMi(1500);
    sleep_ms(100);

    playSol(900);
    sleep_ms(100);
    playLa(500);
    sleep_ms(100);
    playSol(900);
    sleep_ms(100);
    playMi(1500);
    sleep_ms(100);

    playRe(900);
    sleep_ms(100);
    playRe(700);
    sleep_ms(100);
    playSi(1000);
    sleep_ms(100);

    playDo(900);
    sleep_ms(100);
    playDo(700);
    sleep_ms(100);
    playSol(1000);
    sleep_ms(100);

    playLa(900);
    sleep_ms(100);
    playLa(700);
    sleep_ms(100);
    playDo(700);
    sleep_ms(100);
    playSi(400);
    sleep_ms(100);
    playLa(300);
    sleep_ms(100);
    playSol(300);
    sleep_ms(100);
    playLa(200);
    sleep_ms(100);

    playSol(800);
    sleep_ms(100);
    playMi(1000);
    sleep_ms(100);

    playLa(800);
    sleep_ms(100);
    playLa(500);
    sleep_ms(100);
    playDo(500);
    sleep_ms(100);

    playSi(200);
    sleep_ms(100);
    playLa(400);
    sleep_ms(100);
    playSol(600);
    sleep_ms(100);

    playLa(200);
    sleep_ms(100);
    playSol(400);
    sleep_ms(100);
    playMi(1000);
    sleep_ms(100);

    playRe(700);
    sleep_ms(100);
    playRe(300);
    sleep_ms(100);
    playFa(600);
    sleep_ms(100);

    playRe(200);
    sleep_ms(100);
    playSi(400);
    sleep_ms(100);
    playDo(1000);
    sleep_ms(100);
    playMi(1000);
    sleep_ms(100);

    playDo(600);
    sleep_ms(100);
    playSol(200);
    sleep_ms(100);
    playMi(400);
    sleep_ms(100);
    playSol(600);
    sleep_ms(100);
    playFa(200);
    sleep_ms(100);
    playRe(400);
    sleep_ms(100);
    playDo(1000);

void tocar9Sinfonia() {
    // Primeira parte: E E F G G F E D C C D E E D D
    playMi(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playFa(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);
    playFa(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);

    // Segunda parte: E E F G G F E D C C D E D C C
    playMi(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playFa(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);
    playFa(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(200);

    // Terceira parte: D D E C D E F E C D E F E D C D G
    playRe(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playFa(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playFa(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);

    // Quarta parte: E E F G G F E D C C D E D C C
    playMi(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playFa(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);
    playSol(300);
    sleep_ms(200);
    playFa(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playMi(300);
    sleep_ms(200);
    playRe(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(200);
    playDo(300);
    sleep_ms(200);
}

void tocarMarioBrosTheme() {
    // Parte inicial
    playMi(200); 
    sleep_ms(100);
    playMi(200); 
    sleep_ms(100);
    sleep_ms(100);
    playMi(200);
    sleep_ms(100);
    sleep_ms(100);
    playDo(200);
    sleep_ms(100);
    playMi(200);
    sleep_ms(100);
    sleep_ms(100);
    playSol(400); 
    sleep_ms(300);
    playDo(400);
    sleep_ms(300);

    // Continuação
    playDo(200);
    sleep_ms(100);
    playSol(200);
    sleep_ms(100);
    playMi(200);
    sleep_ms(100);
    playLa(200); 
    sleep_ms(100);
    playSi(200); 
    sleep_ms(100);
    playLa(200);
    sleep_ms(100);
    playSol(200);
    sleep_ms(100);
    playMi(150);
    sleep_ms(100);
    playSol(150);
    sleep_ms(100);
    playLa(150);
    sleep_ms(100);
    playSi(200);
    sleep_ms(100);

    // Parte final
    playFa(150); 
    sleep_ms(100);
    playSol(150);
    sleep_ms(100);
    playMi(200);
    sleep_ms(100);
    playDo(200);
    sleep_ms(100);
    playRe(200); 
    sleep_ms(100);
    playSi(200);
    sleep_ms(100);

void printNomeMusica(char musica){
    switch (musica)
    {
    case '1':
        printf("Tocando a música Do Ré Mi\n");
        break;
    case '2':
        printf("Tocando a música Parabéns pra você\n");
        break;
    case '3':
        printf("Tocando a música Cai Cai Balão\n");
        break;
    case '4':
        printf("Tocando a música Brilha Brilha Estrelinha\n");
        break;
    case '5':
        printf("Tocando a música Jingle Bells\n");
        break;
    case '6':
        printf("Tocando a música Noite Feliz\n");
        break;
    case '7':
        printf("Tocando a música Borboletinha\n");
        break;
    case '8':
        printf("Tocando a música Pirulito que bate bate\n");
        break;
    case '9':
        printf("Tocando a música 9 Sinfonia\n");
        break;
    case '*':
        printf("Tocando a música Mario Bros");
        break;
    default:
        break;
    }
}

// Função para ler o comando do terminal
void processarComando(const char *comando) {
    if (strcmp(comando, "green") == 0) {
        gpio_put(GREEN_LED_PIN, 1);
        gpio_put(BLUE_LED_PIN, 0);
        gpio_put(RED_LED_PIN, 0);
    } else if (strcmp(comando, "blue") == 0) {
        gpio_put(BLUE_LED_PIN, 1);
        gpio_put(GREEN_LED_PIN, 0);
        gpio_put(RED_LED_PIN, 0);
    } else if (strcmp(comando, "red") == 0) { 
        gpio_put(RED_LED_PIN, 1);
        gpio_put(GREEN_LED_PIN, 0);
        gpio_put(BLUE_LED_PIN, 0);
    } else if (strcmp(comando, "white") == 0) {
        gpio_put(GREEN_LED_PIN, 1);
        gpio_put(BLUE_LED_PIN, 1);
        gpio_put(RED_LED_PIN, 1);
    } else if (strcmp(comando, "desligar") == 0) {
        gpio_put(GREEN_LED_PIN, 0);
        gpio_put(BLUE_LED_PIN, 0);
        gpio_put(RED_LED_PIN, 0);
    } else if (strcmp(comando, "buzzer") == 0) {
        play_buzzer(BUZZER_PIN, 3350, 2000);
    } else if(strcmp(comando, "musica1") == 0){
        printNomeMusica('1');
        tocarDoReMi();
    } else if(strcmp(comando, "musica2") == 0){
        printNomeMusica('2');
        tocarParabens();
    }else if(strcmp(comando, "musica3") == 0){
        printNomeMusica('3');
        tocarCaiCaiBalao();
    }
    else if(strcmp(comando, "musica4") == 0){
        // Brilha Brilha Estrelinha pode ser adicionada aqui
    }else if(strcmp(comando, "musica5") == 0){
        printNomeMusica('5');
        tocarJingleBells();
    }else if(strcmp(comando, "musica6") == 0){
        printNomeMusica('6');
        tocarNoiteFeliz();
    }else if(strcmp(comando, "musica7") == 0){
        printNomeMusica('7');
        tocarBorboletinha();
    }else if(strcmp(comando, "musica8") == 0){
        printNomeMusica('8');
        tocarPirulitoQueBateBate();
    }else if(strcmp(comando, "musica9") == 0){
        printNomeMusica('9');
        tocar9Sinfonia();
    }else if(strcmp(comando, "musica*") == 0){
        printNomeMusica('*');
        tocarMarioBrosTheme();
    }else if (strcmp(comando, "sair") == 0) {
        printf("Reiniciando o sistema...\n");
        reset_usb_boot(0, 0);  // Reinicia o microcontrolador
    } else {
        printf("Comando inválido. Tente novamente.\n");
    }
}

int main() {
    stdio_init_all();
    init_leds_and_buzzer();

    printf("Bem-vindo! Controle os LEDs e o buzzer da BitDogLab pelo terminal.\n");

    char comando[25];  // Variável para armazenar o comando
    int index = 0; // Índice do buffer de comando

    while (1) {
        ler_comando(comando, sizeof(comando));
        printf("\nComando Detectado: %s\n", comando);
        processarComando(comando); 
    }

    return 0;
}