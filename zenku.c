#include <stdio.h>
typedef char tablero[7][7];

void mostrarOpciones(){
	printf("Para jugar, presiona 1\n");
	printf("Para salir, presiona 9\n");
}

void inicializarTablero(tablero tab){
	int fila, columna;

	for (fila = 0; fila < 7; fila++)
	{
		for (columna = 0; columna < 7; columna++)
		{
			if (fila == 3 && columna == 3)
			{
				tab[fila][columna] = ' ';
			}else{
				if( (fila < 2 || fila > 4)&&(columna < 2 || columna > 4) ){
					tab[fila][columna] = 'X';
				}else{
					tab[fila][columna] = 'O';
				}
			}
		}
	}
}

void mostrarTablero(tablero tab){
	int fila, columna, aux;

	for (fila = 0; fila < 7; fila++)
	{
		if (fila == 0)
			{
				for (aux = 0; aux <= 7; aux++)
				{
					if (aux == 0)
					{
						printf("\t - " );
					}else{
						printf(" %d ", aux);
					}					
				}
				printf("\n");
			}
		printf("\t %d ", fila + 1);
		for (columna = 0; columna < 7; columna++)
		{
			printf(" %c ", tab[fila][columna]);
		}
		printf("\n");
	}
}

int validarMovimiento(int moverFila, int moverColumna, int destinoFila, int destinoColumna, tablero tab){
	// que mueva una ficha, no un espacio vacio o una X
	if (tab[moverFila-1][moverColumna-1] == 'O')
	{
		//que sea un movimiento dentro del tablero
		if ((moverFila < 1 && moverFila > 7) && (destinoFila < 1 && destinoColumna > 7))
		{
			return 0;
		}else{
			// que no se mueva al mismo lugar donde esta
			if (moverFila == destinoFila && moverColumna == destinoColumna)
			{
				return 0;
			}else{
				// que no se mueva en diagonal
				if (moverFila == destinoFila || moverColumna == destinoColumna)
				{	// que se mueva solo 2 espacios
					if ((moverFila - destinoFila == 2 || moverFila - destinoFila == -2) || (moverColumna - destinoColumna == 2 || moverColumna - destinoColumna == -2))
					{
					//que no exista ficha en el lugar de destino, ni que sea una esquina prohibida
						if (tab[destinoFila - 1][destinoColumna - 1] == 'O' || tab[destinoFila - 1][destinoColumna - 1] == 'X')
						{
							return 0;
						}else{
							return 1;
						}
					}else{
						return 0;	
					}
				}else{
					return 0;
				}
			}
		}
	}else{
		return 0;
	}
}

void mover(int moverFila, int moverColumna, int destinoFila, int destinoColumna, tablero tab){
	tab[moverFila - 1][moverColumna - 1] = ' ';
	tab[destinoFila - 1][destinoColumna - 1] = 'O';

	if (moverFila == destinoFila)
	{
		if (moverColumna < destinoColumna)
		{
			tab[moverFila - 1][moverColumna] = ' ';
		}else{
			tab[moverFila - 1][moverColumna - 2] = ' ';
		}
	}else{
		if (moverColumna == destinoColumna)
		{
			if (moverFila < destinoFila)
			{
				tab[moverFila][moverColumna - 1] = ' ';
			}else{
				tab[moverFila - 2][moverColumna - 1] = ' ';
			}
		}
	}
}

void dejarGanar(tablero tab){
	int fila, columna;

	for (fila = 0; fila < 7; fila++)
	{
		for (columna = 0; columna < 7; columna++)
		{
			if (fila == 3 && columna == 3)
			{
				tab[fila][columna] = ' ';
			}else{
				if( (fila < 2 || fila > 4)&&(columna < 2 || columna > 4) ){
					tab[fila][columna] = 'X';
				}else{
					if ((fila == 3 && columna == 2) || (fila == 3 && columna == 1))
					{
						tab[fila][columna] = 'O';
					}else{
						tab[fila][columna] = ' ';
					}
				}
			}
		}
	}
}

int hazGanado(tablero tab){
	int fila, columna, cuentaFichas = 0;

	for (fila= 0; fila < 7; fila++)
	{
		for (columna = 0; columna < 7; columna++)
		{
			if(tab[fila][columna] == 'O')
			{
				cuentaFichas++;
			}
		}
	}

	if (cuentaFichas == 1)
	{
		return 1;
	}else{
		return 0;
	}
}

void opcionesJugar(){
	printf("\n");
	printf("Para jugar, debes ingresar primero la ficha que quieres mover, y luego el lugar donde quieres moverla\n");
	printf("Para llegar de forma inmediata al ultimo movimiento, debes ingresar '9' en todos los campos.\n");
	printf("Para volver al menu principal, debes ingresar '0' en todos los campos.\n");
	printf("Para reiniciar el juego, debes ingresar '8' en todos los campos\n");
	printf("\n");
	printf("Disfruta! :)\n\n");
}


void jugar(){
	int moverFila, moverColumna, destinoFila, destinoColumna, movimientoValido, salida = 0, ganado;
	tablero tab;
	inicializarTablero(tab);
	mostrarTablero(tab);
	ganado = hazGanado(tab);

	opcionesJugar();

	while (salida != 1){
		printf("Ingresa las coordenadas de la ficha que deseas mover\n");
		printf("fila: ");
		scanf(" %i", &moverFila);
		printf("columna: ");
		scanf(" %i", &moverColumna);
		printf("\n");

		printf("Ingresa las coordenadas donde deseas mover la ficha\n");
		printf("fila: ");
		scanf(" %i", &destinoFila);
		printf("columna: ");
		scanf(" %i", &destinoColumna);
		printf("\n");


		if (moverFila == 9 && moverColumna == 9 && destinoFila == 9 && destinoColumna == 9)
		{
			dejarGanar(tab);
			printf("Haz decidido llegar al final del juego. Haz el ultimo movimiento!\n");
			mostrarTablero(tab);
		}else{
			if(moverFila == 0 && moverColumna == 0 && destinoFila == 0 && destinoColumna == 0){
				salida = 1;
			}else{
				if (moverFila == 8 && moverColumna == 8 && destinoFila == 8 && destinoColumna == 8)
				{
					inicializarTablero(tab);
					printf("Haz reiniciado el tablero!\n\n");
					mostrarTablero(tab);
					opcionesJugar();
				}else{
					movimientoValido = validarMovimiento(moverFila, moverColumna, destinoFila, destinoColumna, tab);
					if (movimientoValido == 1)
					{
						printf("Yay!\n");
						mover(moverFila, moverColumna, destinoFila, destinoColumna, tab);
						mostrarTablero(tab);
					}else{
						printf("Movimiento no valido\n");
					}
				}		
			}
		}

		ganado = hazGanado(tab);
		if (salida != 1)
		{
			if (ganado == 1)
			{
				salida = 1;
				printf("\n Haz ganado :')!!!!\n\n");
			}
		}else{
			printf("\nVolver al menu!\n\n");
		}
	}

	mostrarOpciones();
}

void menu(){
	int opcion;

	printf("\t\t Senku \n\n");
	mostrarOpciones();
	
	scanf(" %d", &opcion);
	// el 9 es salir
	while(opcion != 9){
		if (opcion == 1)
		{
			jugar();
		}else{
			if (opcion != 9)
			{
				printf("Opcion no valida\n");
			}
		}
		scanf(" %d", &opcion);
	}

	printf("Hasta pronto, vuelve cuando quieras :)\n");
}

int main()
{
	menu();
	return 0;
}