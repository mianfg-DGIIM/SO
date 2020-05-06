/*
 * esclavo.c
 * 
 * Copyright 2018 mianfg <mianfg@mianfg-PE62-7RD>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char **argv) {
	if ( argc != 3 ) {
		perror("Fallo argumentos\n");
	}
	
	setvbuf(stdout,NULL,_IONBF,0);

	int min, max, primo;
	int es_primo; // esto es un bool
	
	min = atoi(argv[1]);
	max = atoi(argv[2]);
	
	// cálculo de primos
	for ( int n = min; n <= max; n++ ) {
		es_primo = 1;
		for ( int k = 2; k*k <= n && es_primo != 0; k++ ) {
			if ( n % k == 0 ) {
				es_primo = 0;
			}
		}
		if ( es_primo != 0 ) {
			printf("%d\n", n);
		}
	}
	
	return 0;
}

