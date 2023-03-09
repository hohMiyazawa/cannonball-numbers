# cannonball-numbers

https://www.youtube.com/watch?v=q6L06pyt9CA "90,525,801,730 Cannon Balls - Numberphile"

Which n-gonal numbers are themselves pyramids of n-gonal numbers?

This is the generalised version of the cannonball problem, which asks this question about squares and square pyramids.

This is a search algorithm, using the GNU Multi Precision library.

# Build
```
g++ -O3 cannonball.cpp -o cannonball -lgmp
```

# Usage
```
./cannonball 3 10000
```
cannonball startPolygon pyramidLayerLimit

# Conjectures

For all values of ``3 | n + 1``, it appears that there is a pyramid with ``(n - 2)² / 3 - 2`` layers.

Conjecture 1: This holds for all ``3 | n + 1``

Cannonball numbers not of this type (currently 41) are listed in irregular.csv

Conjecture 2: An n-gonal cannonball number must have at least sqrt(n) layers.

# Proven results

There are exactly 4 triangular canonball numbers (10, 120, 1540, 7140), and exactly 1 square canonball number (4900).
