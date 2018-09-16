#include <iostream>
#include <fstream>
#include "cmdline.h"
#include "Sensor.h"
using namespace std;

// ******** Protitipos de funciones de command line ******************

static void opt_input(string const &);
static void opt_output(string const &);
static void optTempSensor(string const &);
static void opt_help(string const &);

// ********************Opciones globales command line***********************

static option_t options[] = {
	{1, "i", "input",  "-", opt_input,  OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "d", "data", NULL, optTempSensor, OPT_MANDATORY},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};
//********************Variables Globales**********************************

static istream *iss = 0;  //archivo de entrada
static ostream *oss = 0;
static fstream ifs;
static fstream ofs;
static ifstream dataBaseFile ;    //

int main(int argc, char * const argv[])
{
	cmdline cmdl(options);
	cmdl.parse(argc, argv);
	// a partir de aca hay que empezar a escribir el codigo usando solo *iss,*oss,
	//ifs,ofs,dataBaseFile , ya que cmdline. ya se encargo de configurar
	//los argumentos de ordenes en linea de comandos
	Sensor  cpu;
	cpu.queryTemp(iss,oss,dataBaseFile);
	return 0;
}






static void opt_input(string const &arg)
{
    // Si el nombre del archivos es "-", usaremos la entrada
    // estándar. De lo contrario, abrimos un archivo en modo
    // de lectura.
    //
    if (arg == "-") {
        iss = &cin;
    } else {
        ifs.open(arg.c_str(), ios::in);
        iss = &ifs;
    }

    // Verificamos que el stream este OK.
    //
    if (!iss->good()) {
        cerr << "cannot open "
        << arg
        << "."
        << endl;
        exit(1);
    }
}
static void
opt_output(string const &arg)
{
    // Si el nombre del archivos es "-", usaremos la salida
    // estándar. De lo contrario, abrimos un archivo en modo
    // de escritura.
    //
    if (arg == "-") {
        oss = &cout;
    } else {
        ofs.open(arg.c_str(), ios::out);
        oss = &ofs;
    }

    // Verificamos que el stream este OK.
    //
    if (!oss->good()) {
        cerr << "cannot open "
        << arg
        << "."
        << endl;
        exit(1);
    }
}
static void optTempSensor(string const &arg)
{
	dataBaseFile.open(arg.c_str()) ;

		if (!dataBaseFile.good()) {
			cerr << "No se puede abrir el archivo :" << arg << "." << endl ;
			exit(EXIT_FAILURE) ;
		}

}


static void opt_help(string const &arg)
{
    cout << "CmdLine -d database -i input -o output"
    << endl;
    exit(0);
}
