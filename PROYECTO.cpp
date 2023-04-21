#include<windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define max 20
//------------------------------------------------------definicion de estructuras
struct fecha {
int dia,mes,anio;
};
struct cliente {
	char nombre [20],cedula[13];
};

struct producto {
	struct fecha fecha_producto;
	struct cliente datos_cliente;
	int codigo;
	char producto_nombre[30];
	double precio; 
    int cantidad;
	double total_pagar;	
};
//----------------------------------------------------------coordenas  para el diseño del marco
void gotoxy(int x, int y) { 
	HANDLE hcon; 
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos; dwPos.X = x;dwPos.Y = y;
	SetConsoleCursorPosition (hcon, dwPos); 
}
void color(int X) 
{ 
SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),X); 
} 
//------------------------------------------------------------------------------- prototipos

void integrantes();
void pintar_limites ();
int Menu();
void llenarproducto(int seleccion,struct producto *bazar);
double calculo_descuento(int cantidad);
void imprimir_venta(struct producto bazar);
void busqueda_cliente(struct producto bazar[],char producto_busqueda[],int n);
void busqueda_articulos(struct producto bazar[max],int codigo,int n);
void busqueda_fecha(struct producto bazar[max],int dia,int mes ,int anio,int n);

//-------------------------------------------------------------------------------funcion principal main
main(){
	pintar_limites ();
	integrantes();
	int i=0,seleccion=0,x,codigo,dia,mes,anio;
	char porducto_busqueda[30],regresar;
	struct producto bazar[max];
	int opcion=0;
inicio:

do{	
	while(opcion<5){	
	    opcion=Menu();
			switch(opcion){
				
				case 1:  //------------------------------------------ Registrar las ventas del cliente
					 
					registro:
					do{  
					pintar_limites();
					color(4);gotoxy(23,13);	printf("FACTURA NUMERO : %d\n",i+1);
					color(7);gotoxy(23,15);	printf("1.- Chompas");
					color(7);gotoxy(23,16);printf("2.- Camisetas");
					color(7);gotoxy(23,17);printf("3.- Gorras");
					color(7);gotoxy(23,18);printf("4.- Llaveros variados ");
					color(7);gotoxy(23,19);printf("5.- Esferograficos variados \n");
					color(9);gotoxy(23,21);printf ("Seleccione una opcion -->");scanf ("%d",&seleccion);color(10); fflush(stdin);
					}while (seleccion<=0||seleccion>=6);
					printf("\n");
					system ("cls");
					pintar_limites();
				    color(4);gotoxy(23,12);printf("FACTURA NUMERO : %d",i+1);
					llenarproducto(seleccion,&bazar[i]);
					system("cls");
				    imprimir_venta(bazar[i]);
               	     i++;
	                color(9);gotoxy(23,28);printf ("DESEA REGISTRAR OTRA FACTURA s/n ->");scanf("%s",&regresar);color(10);	
                      	if (regresar=='s'){
		                	system ("cls");
	                            goto registro;
                           	}
                     	else {		
                         	goto inicio;
	                    }
					system("pause");
				break;	 
				case 2: //------------------------------------------ Consultar las ventas del cliente
					consulta:
						pintar_limites();
					color(4);gotoxy(23,12);printf("IDENTIFICACION ");
					color(7);gotoxy(23,15);printf("INGRESE LA CEDULA ->");
					scanf("%s",porducto_busqueda);fflush(stdin);
					system("cls");
					busqueda_cliente(bazar,porducto_busqueda,i);
	                color(9);gotoxy(23,28);printf ("DESEA CONSULTAR OTRO CLIENTE s/n ->");
	                scanf("%s",&regresar);	
	                    if (regresar=='s'){
		                   system ("cls");
	                        goto consulta;
	                    }
                     	else {
                        	goto inicio;
	                    }
					    system("pause");
				break;
				case 3: //-------------------------------------------Consultar con el codigo del producto
				articulo:
					pintar_limites();
					color(4);gotoxy(23,12);printf("CODIGO DEL PRODUCTO");
					color(7);gotoxy(23,15);printf("INGRESE EL CODIGO: ");
					scanf("%d",&codigo);fflush(stdin); 
					system("cls");
					busqueda_articulos(bazar, codigo,i);
		            color(9);gotoxy(23,28);printf ("DESEA BUSCAR DENUEVO EL CODIGO s/n ->");
		            scanf("%s",&regresar);	
	                	if (regresar=='s'){
			            	system ("cls");
	                    	goto articulo;
		                }
		                else {
		                    goto inicio;
		                }
					system("pause");
				break;
				case 4:
				fecha: //---------------------------------------------Resumen de las ventas del cliente a traves de la fecha
					pintar_limites();
					color(4);gotoxy(23,12);printf("FECHA ");
					color(7);gotoxy(23,15);printf("Dia -> ");scanf("%d",&dia);fflush(stdin);
					color(7);gotoxy(23,16);printf("Mes -> ");scanf("%d",&mes);fflush(stdin);
					color(7);gotoxy(23,17);printf("A%co: ",164);scanf("%d",&anio);fflush(stdin);
					system("cls");
					busqueda_fecha(bazar,dia,mes,anio,i);
					color(9);gotoxy(23,28);printf ("DESEA BUSCAR DENUEVO LA FEHCA s/n ->");
		            scanf("%s",&regresar);	
		                if (regresar=='s'){
			            	system ("cls");
		                    goto fecha;
		                 }
		                else {
		                   goto inicio;
	                    	}
				    	system("pause");
				break;
				case 5:  //-----------------------------------salir 
			    exit(0);
				break;
			}
		}
	}while(i>=max||i<=0);
	return 0;
}
//----------------------------------------------------------------funcion menu
int Menu()
{	
	int opcion=0;
	do
	{
		system("cls"); pintar_limites();
		color(4);gotoxy(23,13);printf("Menu de opciones");
		printf("\n");
		color(7);gotoxy(23,15);printf("1.- Registrar venta");
		color(7);gotoxy(23,16);printf("2.- Consultar ventas del cliente ");
		color(7);gotoxy(23,17);printf("3.- Consultar articulos vendidos ");
		color(7);gotoxy(23,18);printf("4.- Resumen de ventas");
		color(7);gotoxy(23,19);printf("5.- Salir");
		fflush(stdin);
		color(9);gotoxy(23,21);printf("Seleccione la opcion => ");
		scanf("%d", &opcion);color(10);fflush(stdin);
		system("cls");
	}while(opcion<1 || opcion>5);
	return opcion;
}
//--------------------------------------------------------------------------------diseño 
void integrantes(){
    color(9);gotoxy(14,5);printf ("*------------------------------------------------*");
	color(4);gotoxy(14,7);printf ("            UNIVERSIDAD DE GUAYAQUIL              ");
	color(4);gotoxy(14,8);printf ("    FACULTAD DE CIENCIAS MATEMATICAS Y FISICAS   ");
	color(4);gotoxy(14,9);printf ("      INGENIERIA EN SISTEMAS COMPUTACIONALES     ");
	gotoxy(14,10);printf("                                                 ");
	color(5);gotoxy(14,11);printf("             ::::::INTEGRANTES:::::              ");
	gotoxy(14,12);printf("                                                  ");
    color(7);gotoxy(14,13);printf("      -Chilan Holguin Edwin                      ");
    color(7);gotoxy(14,14);printf("      -Basurto Eduardo                           ");
    color(7);gotoxy(14,15);printf("      -Salazar Christopher                       ");
    color(7);gotoxy(14,16);printf("      -Realpe Melendres Carlos                   ");
    gotoxy(14,17);printf("                                                 ");
    color(7);gotoxy(14,18);printf("       Curso : 2-2                               ");
    color(7);gotoxy(14,19);printf("       MATERIA:PROGRAMACION II                   ");
    color(7);gotoxy(14,20);printf("       DOCENTE:ING. MIGUEL MOLINA CALDERON       ");
	gotoxy(14,21);printf("                                                  ");
	color(5);gotoxy(14,22);printf("                TEMA DE PROYECTO                ");
	color(6);gotoxy(14,24);printf(" Bazar de recuerdos de la UG(facturas de ventas) ");
	gotoxy(14,25);printf("                                                 ");
	color(9);gotoxy(14,26);printf("*------------------------------------------------*");
	system ("Pause>null");
system ("cls");
}
//--------------------------------------------------------------------------------diseño del marco
void pintar_limites () { 
     for(int i=2; i<78; i++){ 
     	color(5);gotoxy(i,3); printf("%c",205); color(10);//parte superior
     	color(5);gotoxy(i,33); printf("%c",205);color(10 );//parte inferior
	 }
	 for(int i=4; i<33; i++){ // diseño vertical de la pantalla
	 	color(5);gotoxy(2,i); printf("%c",186);color(10); //izquierda 
	 	color(5);gotoxy(77,i); printf("%c",186);color(10);//derecha
	 }
	 //diseño de las esquinas de la pantalla 
	 color(5);gotoxy(2,3); printf("%c",201);color(10);
	 color(5);gotoxy(2,33); printf("%c",200);color(10);
	 color(5);gotoxy(77,3); printf("%c",187);color(10);
	 color(5);gotoxy(77,33); printf("%c",188);color(10);
}		
//---------------------------------------------------------------------------------llenar datos de los productos
void llenarproducto(int codigo,struct producto *bazar){
	float des;
	char nombre[30];
	switch(codigo){
	case 1:
		pintar_limites();
		bazar->codigo=1;
		color(7);gotoxy(23,14);printf("Fecha de compra ");fflush(stdin);
		color(7);gotoxy(23,16);printf("Ingrese el dia: ");fflush(stdin);scanf("%d",&bazar->fecha_producto.dia);
		color(7);gotoxy(23,17);printf("Ingrese el mes: ");fflush(stdin);scanf("%d",&bazar->fecha_producto.mes);
		color(7);gotoxy(23,18);printf("Ingrese el  a%co: ",164);fflush(stdin);scanf("%d",&bazar->fecha_producto.anio);
		color(7);gotoxy(23,19);printf("Ingrese nombre del cliente: ");fflush(stdin);gets(nombre);
		strcpy(bazar->datos_cliente.nombre,nombre);
		color(7);gotoxy(23,20);printf("Ingrese cedula del cliente: ");fflush(stdin);
		gets(nombre);
		strcpy(bazar->datos_cliente.cedula,nombre);
		strcpy(bazar->producto_nombre,"Chompas Ug");
		bazar->precio=35;
		color(7);gotoxy(23,21);printf("Ingrese la cantidad de articulos a comprar ");fflush(stdin);
		scanf("%d",&bazar->cantidad);
		des=calculo_descuento(bazar->cantidad);
		bazar->total_pagar=bazar->cantidad*35*des;
	break;
	case 2:
		bazar->codigo=2;
		color(7);gotoxy(23,15);printf("Ingrese el dia: ");fflush(stdin);scanf("%d",&bazar->fecha_producto.dia);
		color(7);gotoxy(23,16);printf("Ingrese el mes: ");fflush(stdin);scanf("%d",&bazar->fecha_producto.mes);
		color(7);gotoxy(23,17);printf("Ingrese el a%co: ",164);fflush(stdin);scanf("%d",&bazar->fecha_producto.anio);
		color(7);gotoxy(23,18);printf("Ingrese nombre del cliente: ");fflush(stdin);gets(nombre);
		strcpy(bazar->datos_cliente.nombre,nombre);
		color(7);gotoxy(23,19);printf("Ingrese cedula del cliente: ");fflush(stdin);gets(nombre);
		strcpy(bazar->datos_cliente.cedula,nombre);
		strcpy(bazar->producto_nombre,"Camisetas Ug");
		bazar->precio=15;
		color(7);gotoxy(23,20);printf("Ingrese la cantidad de articulos a comprar ");fflush(stdin);
		scanf("%d",&bazar->cantidad);
		des=calculo_descuento(bazar->cantidad);
		bazar->total_pagar=bazar->cantidad*15*des;
	break;
	case 3:
		bazar->codigo=3;
		color(7);gotoxy(23,15);printf("Ingrese el dia: ");fflush(stdin);scanf("%d",&bazar->fecha_producto.dia);
		color(7);gotoxy(23,16);printf("Ingrese el mes: ");fflush(stdin);scanf("%d",&bazar->fecha_producto.mes);
		color(7);gotoxy(23,17);printf("Ingrese el a%co: ",164);fflush(stdin);scanf("%d",&bazar->fecha_producto.anio);
		color(7);gotoxy(23,18);printf("Ingrese nombre del cliente: ");fflush(stdin);		gets(nombre);
		strcpy(bazar->datos_cliente.nombre,nombre);
		color(7);gotoxy(23,19);printf("Ingrese cedula del cliente: ");fflush(stdin);		gets(nombre);
		strcpy(bazar->datos_cliente.cedula,nombre);
		strcpy(bazar->producto_nombre,"Gorras Ug");
		bazar->precio=8;
		color(7);gotoxy(23,20);printf("Ingrese la cantidad de articulos a comprar ");fflush(stdin);
		scanf("%d",&bazar->cantidad);
		des=calculo_descuento(bazar->cantidad);
		bazar->total_pagar=bazar->cantidad*8*des;
	break;
	case 4:
		bazar->codigo=4;
		color(7);gotoxy(23,15);printf("Ingrese el dia: ");fflush(stdin);scanf("%d",&bazar->fecha_producto.dia);
		color(7);gotoxy(23,16);printf("Ingrese el mes: ");fflush(stdin);scanf("%d",&bazar->fecha_producto.mes);
		color(7);gotoxy(23,17);printf("Ingrese a%co: ",164);fflush(stdin);scanf("%d",&bazar->fecha_producto.anio);
		color(7);gotoxy(23,18);printf("Ingrese nombre del cliente: ");fflush(stdin);gets(nombre);
		strcpy(bazar->datos_cliente.nombre,nombre);
		color(7);gotoxy(23,19);printf("Ingrese cedula del cliente: ");fflush(stdin);
		gets(nombre);
		strcpy(bazar->datos_cliente.cedula,nombre);
		strcpy(bazar->producto_nombre,"Llaveros variados");
		bazar->precio=3;
		color(7);gotoxy(23,20);printf("Ingrese la cantidad de articulos a comprar ");fflush(stdin);
		scanf("%d",&bazar->cantidad);
		des=calculo_descuento(bazar->cantidad);
		bazar->total_pagar=bazar->cantidad*3*des;
	break;
	case 5:
		bazar->codigo=5;
		color(7);gotoxy(23,17);printf("Ingrese el dia: ");fflush(stdin);scanf("%d",&bazar->fecha_producto.dia);
		color(7);gotoxy(23,16);printf("Ingrese el mes: ");fflush(stdin);scanf("%d",&bazar->fecha_producto.mes);
		color(7);gotoxy(23,17);printf("Ingrese el a%co: ",164);fflush(stdin);scanf("%d",&bazar->fecha_producto.anio);
		color(7);gotoxy(23,18);printf("Ingrese nombre del cliente: ");fflush(stdin);
		gets(nombre);
		strcpy(bazar->datos_cliente.nombre,nombre);
		color(7);gotoxy(23,19);printf("Ingrese cedula del cliente: ");fflush(stdin);
		gets(nombre);
		strcpy(bazar->datos_cliente.cedula,nombre);
		strcpy(bazar->producto_nombre,"Esferograficos variados");
		bazar->precio=2;
		color(7);gotoxy(23,20);printf("Ingrese la cantidad de articulos a comprar ");fflush(stdin);
		scanf("%d",&bazar->cantidad);
		des=calculo_descuento(bazar->cantidad);
		bazar->total_pagar=bazar->cantidad*2*des;
	break;
	}
	color(7);gotoxy(23,17);printf("Venta registrada ");
	printf("La cantidad a pagar es $%.2lf:",bazar->total_pagar);
}
//------------------------------------------------------------------------------------------- visualizar las ventas
void imprimir_venta(struct producto bazar){         
pintar_limites();  
	int cantidad;
	color(4);gotoxy(23,12);printf ("%d / %d  / %d ",bazar.fecha_producto.dia, bazar.fecha_producto.mes, bazar.fecha_producto.anio);
	color(7);gotoxy(23,14);printf("%s con cedula: %s ",bazar.datos_cliente.nombre, bazar.datos_cliente.cedula); 
	color(7);gotoxy(23,16);printf("Producto %s ",bazar.producto_nombre);             
	color(7);gotoxy(23,18);printf("Precio unitario :%.2lf ",bazar.precio);
	color(7);gotoxy(23,20);printf("Cantidad :%d ",bazar.cantidad);
	cantidad = bazar.cantidad;
	if(cantidad>0&&cantidad<6){
	
	}else if(cantidad >=6&&cantidad <=11){
		color(5);gotoxy(23,22);printf("Su descuento fue de 5%c ",37);
	}else if (cantidad>=12&&cantidad<=23){
		color(5);gotoxy(23,22);printf("Su descuento fue de 8%c ",37); 
	}else if(cantidad>23){
		color(5);gotoxy(23,22);printf("Su descuento fue de 15%c ",37);
	}
	color(5);gotoxy(23,24);printf("Precio total : $%3.2lf ",bazar.total_pagar);

}
//-------------------------------------------------------------------------Busqueda de cliente por el numero de cedula
void busqueda_cliente(struct producto bazar[max],char producto_busqueda[13],int n){
	float toltal=0;
	int i;
	for(i=0;i<n;i++){
		if((strcmp(producto_busqueda,bazar[i].datos_cliente.cedula))==0){
			imprimir_venta(bazar[i]);
			toltal=bazar[i].total_pagar+toltal;
		}
	}
	if(toltal!=0){
		color(5);gotoxy(23,23);printf("EL TOTAL DE LAS VENTAS FUERON: $%.2f",toltal);
	}else {
		color(6);gotoxy(23,23);printf("ERROR: EL CLIENTE NO SE ENCUENTRA EN LA BASE DE DATOS ");
	}
}
//-----------------------------------------------------------------------Busqueda de articulos vendidos a traves del codigo de cada producto
void busqueda_articulos(struct producto bazar[max],int codigo,int n){
	float total=0;
	int i;
	for(i=0;i<n;i++){
		if(codigo==bazar[i].codigo){
		imprimir_venta(bazar[i]);
			total=bazar[i].total_pagar+total;
		}
	}
	if(total!=0){
		color(5);gotoxy(23,23);printf("EL TOTAL DE LAS VENTAS FUERON:: $%.2f",total);
	}else {
		color(5);gotoxy(23,23);printf("ERROR: NO HAY VENTAS CON EL CODIGO SELECCIONADO ");
	}
}
//------------------------------------------------------------------------------------- verificar si la fecha esta registrada
void busqueda_fecha(struct producto bazar[max],int dia,int mes ,int anio,int n){
	float total=0;
	int i;
	for(i=0;i<n;i++){
		if(dia== bazar[i].fecha_producto.dia&&mes== bazar[i].fecha_producto.mes&&anio== bazar[i].fecha_producto.anio){
		imprimir_venta( bazar[i]);
			total= bazar[i].total_pagar+total;
		}
	}
	if(total!=0){
		color(5);gotoxy(23,23);printf("Las ventas totales en el dia fueron de: $%.2f",total);
	}else {
		color(5);gotoxy(23,23);printf("ERROR: LA FECHA INGRESADA NO SE ENCUENTRA EN LA BASE DE DATOS ");
	}
}
//------------------------------------------------------------------------------------- calculo de los descuentos correspondientes a cada caso 
double calculo_descuento(int cantidad){
	if(cantidad>0&&cantidad<6){
		return 1;
	}else if(cantidad >=6&&cantidad <=11){
		return 0.95;
	}else if (cantidad>=12&&cantidad<=23){
		return 0.92; 
	}else if(cantidad>23){
		return 0.85;
	}
		
}

