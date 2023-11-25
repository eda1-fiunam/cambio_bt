/*Copyright (C) 
 * 2018 - eda1 dot fiunam at yahoo dot com dot mx
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */

// Programa modificado el 2020-2

#include <stdlib.h>
#include <stdio.h>

#include <stdbool.h>
// para bool, true y false


bool es_factible( int c, int p, int acum )
{
   return ( c + acum ) <= p ? true : false;
}

bool es_solucion( int p, int acum )
{
   return acum == p;
}

/**
 * @brief Determina las denominaciones para un cambio dado.
 *
 * @param c[] Conjunto de candidatos
 * @param i Índice 'libre' para el conjunto de candidatos
 * @param j Tamaño del conjunto de candidatos
 * @param s[] Conjunto solución
 * @param s_idx Índice 'libre' para el conjunto solución
 * @param p Cambio por dar
 * @param acum Acumulador interno
 *
 * @return true si se encontró una solución. false en caso contrario. 
 */
bool bt( int c[], int i, int j, int s[], int *s_idx, int p, int *acum )
{
   bool success = false;
   // termina cuando encuentre una solución

   fprintf( stdout, "====> Llegando con i=%d\n", i );

   for( int x = i; x < j; ++x ) {

      if( success == true ) { return true; }
      // ya no revisa los candidatos restantes una vez que obtuvo una
      // solución

      fprintf( stdout, "\nProbando al candidato <%d>\n", c[x] );

      if( es_factible( c[x], p, *acum ) ) 
      {
         // registra al candidato:
         int cand = c[x];

         s[*s_idx] = cand;
         ++*s_idx;
         *acum += cand;

         fprintf( stdout,  "  + Registrando al candidato <%d>\n", cand );

         if( ! es_solucion( p, *acum ) )
         {
            success = bt( c, x + 1, j, s, s_idx, p, acum );

            if( ! success ) {

               // cancela el registro:
               --*s_idx;
               *acum -= cand;

               fprintf( stdout, "  - Borrando al candidato <%d>\n", cand );
            }
         } else {
            fprintf( stdout, "!Encontré una solución!\n" );
            return true;
         }
      } else {
         printf( "   El candidato <%d> no es factible\n", c[x] );
      }
   }

   printf( "Se terminaron los candidatos\n" );

   fprintf( stdout, "<==== Saliendo cuando i=%d\n", i );
   return false;
}



/**
 * @brief Función de activación
 *
 * @param c[] Conjunto de candidatos
 * @param tam_c Número de candidatos
 * @param s[] Conjunto solución
 * @param tam_s Número máximo de elementos en el conjunto solución
 * @param p El cambio que queremos dar
 *
 * @return El tamaño del conjunto solución; si es cero, entonces no se encontró
 * ninguna solución
 */
int cambio( int c[], int tam_c, int s[], int tam_s, int p )
{
   int acum = 0;
   int s_idx = 0;

   bool res = bt( 
         c, 0, tam_c, // envía al conjunto de candidatos completo
         s, &s_idx,   // conjunto solución
         p,           // instancia particular del problema
         &acum );     // acumulador

   return res ? s_idx : 0;
}

#define MAX_CAND 5

int main( void )
{
   int candidatos[MAX_CAND] = { 2, 5, 3, 5, 1 };

   int solucion[MAX_CAND] = {0};
   // a lo más, habrá MAX_CAND monedas

   int p = 10;
   printf( "Cantidad:\n $ " );
   scanf( "%d", &p );

   int num_monedas = cambio( candidatos, MAX_CAND, solucion, MAX_CAND, p );

   if ( num_monedas > 0 ) 
   {
      printf( "La solución tiene %d monedas: ", num_monedas );

      for( int i = 0; i < num_monedas; ++i ) { printf( "%d, ", solucion[i] ); }
      // imprime al conjunto solución

      printf( "\n" );
   } 
   else 
   {
      printf( "No encontré una solución\n" );
   }

   return 0;
}
