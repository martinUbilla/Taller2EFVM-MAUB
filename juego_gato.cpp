//Emily Volta Miranda 20.718.229-k ; Martín Ubilla Briceño 20.751.624-4
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Representación del tablero como un vector de caracteres
vector<char> tablero = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

// Función para mostrar el tablero
void printTablero() {
    cout << " " << tablero[0] << " | " << tablero[1] << " | " << tablero[2] << "\n";
    cout << "---|---|---\n";
    cout << " " << tablero[3] << " | " << tablero[4] << " | " << tablero[5] << "\n";
    cout << "---|---|---\n";
    cout << " " << tablero[6] << " | " << tablero[7] << " | " << tablero[8] << "\n";
}

// Verifica si hay un ganador
char verificar() {
    // Combinaciones ganadoras
    const int combGanar[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Filas
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columnas
        {0, 4, 8}, {2, 4, 6}             // Diagonales
    };

    for (auto& comb : combGanar) {
        if (tablero[comb[0]] == tablero[comb[1]] && tablero[comb[1]] == tablero[comb[2]]) {
            return tablero[comb[0]]; // Devuelve el ganador ('X' o 'O')
        }
    }
    return (count(tablero.begin(), tablero.end(), 'X') + count(tablero.begin(), tablero.end(), 'O') == 9) ? 'D' : 'N';
    // 'D' para empate, 'N' para continuar
}

// Función para realizar un movimiento
bool movimientor(int pos, char player) {
    if (pos >= 1 && pos <= 9 && tablero[pos - 1] == ('0' + pos)) {
        tablero[pos - 1] = player;
        return true;
    }
    return false;
}

// Evaluación del tablero
int evaluarTab(char computadora, char jugador) {
    char ganador = verificar();
    if (ganador == computadora) return 10;
    if (ganador == jugador) return -10;
    return 0;
}

// Implementación de Minimax
int minimax(bool esMaximo, char computadora, char jugador, int depth) {
    char ganador = verificar();
    if (ganador != 'N') return evaluarTab(computadora, jugador); // Fin del juego

    int mejorPuntaje = esMaximo ? -1000 : 1000;

    for (int i = 0; i < 9; i++) {
        if (tablero[i] != 'X' && tablero[i] != 'O') {
            char aux = tablero[i];
            tablero[i] = esMaximo ? computadora : jugador;
            int puntaje = minimax(!esMaximo, computadora, jugador, depth + 1);
            tablero[i] = aux;

            mejorPuntaje = esMaximo ? max(mejorPuntaje, puntaje) : min(mejorPuntaje, puntaje);
        }
    }
    return mejorPuntaje;
}

// movimiento de la IA con Minimax
int encontMejorMov(char computadora, char jugador) {
    int mejorMov = -1, mejorPuntaje = -1000;
    // int alpha = -1000, beta = 1000; Inicialización de alpha y beta para el algoritmo minimaxAlphaBeta
    for (int i = 0; i < 9; i++) {
        if (tablero[i] != 'X' && tablero[i] != 'O') {
            char aux = tablero[i];
            tablero[i] = computadora;
            //int puntajeMov = minimaxAlphaBeta(false, computadora, jugador, 0, alpha, beta); Implementación de minimaxAlphaBeta
            int puntajeMov = minimax(false, computadora, jugador, 0);
            tablero[i] = aux;

            if (puntajeMov > mejorPuntaje) {
                mejorPuntaje = puntajeMov;
                mejorMov = i + 1; 
            }
        }
    }
    return mejorMov;
}

// Poda Alfa-Beta
int minimaxAlphaBeta(bool esMaximo, char computadora, char jugador, int depth, int alpha, int beta) {
    char ganador = verificar();
    if (ganador != 'N') return evaluarTab(computadora, jugador);

    int mejorPuntaje = esMaximo ? -1000 : 1000;

    for (int i = 0; i < 9; i++) {
        if (tablero[i] != 'X' && tablero[i] != 'O') {
            char aux = tablero[i];
            tablero[i] = esMaximo ? computadora : jugador;
            int puntaje = minimaxAlphaBeta(!esMaximo, computadora, jugador, depth + 1, alpha, beta);
            tablero[i] = aux;

            if (esMaximo) {
                mejorPuntaje = max(mejorPuntaje, puntaje);
                alpha = max(alpha, mejorPuntaje);
            } else {
                mejorPuntaje = min(mejorPuntaje, puntaje);
                beta = min(beta, mejorPuntaje);
            }
            if (beta <= alpha) break; // Poda
        }
    }
    return mejorPuntaje;
}

// Bucle principal del juego
int main() {
    char computadora = 'X', jugador = 'O';
    cout << "¿Quieres ser el primer jugador? (s/n): ";
    char opcion;
    cin >> opcion;
    while(opcion != 's'  && opcion != 'n') {
         cin.clear();
        cin.ignore(1000, '\n'); 
        cout << "Por favor, ingresa una opción válida (s/n): ";
        cin >> opcion;
    }
    bool turnoJug = (opcion == 's' || opcion == 'S');

    while (verificar() == 'N') {
        printTablero();

        if (turnoJug) {
            int movimiento;
            cout << "Tu turno [1-9]: ";
            cin >> movimiento;
            while(cin.fail()){
                cin.clear();
                cin.ignore(1000, '\n'); 
                cout << "Por favor, ingresa un numero valido [1-9]: ";
                cin >> movimiento;
            }
            if (!movimientor(movimiento, jugador)) {
                cout << "movimiento incorrecto. Intenta de nuevo :) .\n";
                continue;
            }
        } else {
            int mejorMov = encontMejorMov(computadora, jugador);
            cout << "La PC elige: " << mejorMov << "\n";
            movimientor(mejorMov, computadora);
        }

        turnoJug = !turnoJug;
    }

    printTablero();
    char ganador = verificar();
    if (ganador == 'D') cout << "-----¡Empate!-----\n";

    else cout << "El ganador es: " << ganador << "\n";

    return 0;
}

