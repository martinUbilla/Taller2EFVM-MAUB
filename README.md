# Taller2EFVM-MAUB
## Integrantes
**Emily Franchesca Volta Miranda; 20.718.229-k; emily.volta@alumnos.ucn.cl; Paralelo C2**

**Martín Alejandro Ubilla Briceño; 20.751.624-4; martin.ubilla@alumnos.ucn.cl; Paralelo C2**
## Descripción del taller
Este es un programa que implementa el juego del gato (tic-tac-toe), con una inteligencia artificial que utiliza los algoritmos Minimax y Poda Alfa-Beta para tomar decisiones óptimas.
## Modo de uso
1. Compilación `g++ -g -o juego .\Taller2Gato.cpp`.
2. Ejecutar juego.exe.
3. Instrucciones de Juego
   - El programa te preguntará si deseas ser el primer jugador (ingresa `s` para sí, `n` para no)
   - Para realizar un movimiento, ingresa un número entre 1 y 9 correspondiente a la posición del tablero:
  
 1 | 2 | 3
---|---|---
 4 | 5 | 6      
 7 | 8 | 9

 
   - El juego terminará cuando haya un ganador o el tablero esté lleno.

**Nota**
- En el código están implementados los dos algoritmos, solo que está por defecto el Minimax. Para utilizar el otro algoritmo Minimax con la poda Alfa y Beta solo hay que descomentar la linea 82 y comentar la linea 83.

## Algoritmos utilizados
 **Minimax**
 El algoritmo Minimax se utiliza para encontrar el mejor movimiento posible en juegos de dos jugadores. Asume que ambos jugadores juegan de manera óptima: uno intenta maximizar su puntuación y el otro minimizarla.

 **Funcionamiento del Algoritmo**
  1. El árbol de decisiones se construye desde el estado actual hasta los posibles estados terminales.
  2. Las hojas del árbol son evaluadas según una función de puntuación:
   - +10: Si Max gana.
   - -10: Si Min gana.
   - 0: Si es empate.
  3. Las puntuaciones se propagan hacia arriba del árbol:
   - En los turnos de Max, se selecciona la puntuación máxima.
   - En los turnos de Min, se selecciona la puntuación mínima.
   
 **Poda Alfa-Beta**
 La Poda Alfa-Beta es una optimización del algoritmo Minimax que reduce el número de nodos explorados, descartando aquellas ramas que no afectan el resultado final. La poda mejora la eficiencia sin alterar el 
 resultado de la búsqueda.
 **Funcionamiento de la Poda Alfa-Beta**
   1. Introduce dos valores:
   - Alpha (α): El mejor valor que Max puede garantizar.
   - Beta (β): El mejor valor que Min puede garantizar.
   2. Durante la evaluación del árbol de decisiones, si en cualquier momento β ≤ α, se corta la rama (poda) porque no cambiará el resultado final.
 **Diagrama del Árbol de Juego**
   El siguiente diagrama muestra un árbol de decisiones simplificado para los primeros 3 movimientos en el juego:


 ## Complejidad del Algoritmo
 **Minimax (sin poda)**
 - Complejidad Temporal: 
  𝑂(𝑏<sup>d</sup>), donde:
   - b: Factor de ramificación (movimientos posibles).
   - d: Profundidad del árbol (turnos restantes).<br>

En el juego del gato:
 - 𝑏 ≈ 9, 8, 7, …
 - d=9 (en el peor caso).<br>

**Poda Alfa-Beta**
- Complejidad Temporal: 
𝑂(𝑏<sup>𝑑/2</sup>) en el mejor caso (cuando las ramas se evalúan en el orden óptimo).<br>

**Ejemplo Comparativo**
- Sin Poda (Minimax):
  Con 𝑏=9, 𝑑=3
    - Nodos evaluados: 9<sup>3</sup>=729
- Con poda Alfa-Beta:
  Con 𝑏=9, 𝑑=3
    - Nodos evaluados (mejor caso): 9<sup>3/2</sup>≈81
