#include <iostream>
#include <stdio.h>

using namespace std; //isso me livra de tanta resolucao de escopo

class Relogio {
    private:
    int hora;
    int minuto;
    int segundo;
	
	public:
	Relogio(int hora, int minuto, int segundo); //diferente ter que declarar método assim...
	~Relogio();
	int getHora();
	void setHora(int hora);
	int getMinuto();
	void setMinuto(int minuto);
	int getSegundo();
	void setSegundo(int segundo);
	void ajustar(int incrementoHora, int incrementoMinuto, int incrementoSegundo);
};

	Relogio::Relogio(int hora, int minuto, int segundo) { //resolucao de escopo comecou a ficar mais clara
		setHora(hora);
		setMinuto(minuto);
		setSegundo(segundo);
	}
	
	Relogio::~Relogio() {
	}
	
	int Relogio::getHora() {
		return hora;
	}
	
	void Relogio::setHora(int hora) {
		this->hora = hora; //estive me perguntando quando teria que usar '->', agora descobri
	}
	
	int Relogio::getMinuto() {
		return minuto;
	}
	
	void Relogio::setMinuto(int minuto) {
		this->minuto = minuto;
	}
	
	int Relogio::getSegundo() {
		return segundo;
	}
	
	void Relogio::setSegundo(int segundo) {
		this->segundo = segundo;
	}
	
	void Relogio::ajustar(int incrementoHora, int incrementoMinuto, int incrementoSegundo) {
		int segundoAdicional = getSegundo();
		int segundoAtual = incrementoSegundo + getSegundo();
		if (segundoAtual>59) {
			int minutoAdicional = (int) segundoAtual/60;
			incrementoMinuto+= minutoAdicional;
		}
		segundoAtual = segundoAtual % 60;
		setSegundo(segundoAtual);
		
		int minutoAtual = incrementoMinuto + getMinuto();
		if (minutoAtual>59) {
			int horaAdicional = (int) minutoAtual/60;
				incrementoHora+= horaAdicional;
		}
		minutoAtual = minutoAtual % 60;
		setMinuto(minutoAtual);
		
		int horaAtual = (incrementoHora + getHora()) % 24;
		setHora(horaAtual);
	}

int main()
{
    int hora, minuto, segundo;
    int numeroAjustes, i;
    int incrementoHora = 0, incrementoMinuto = 0, incrementoSegundo = 0;
    string incremento;
    cin >> hora;
    cin >> minuto;
    cin >> segundo;
	Relogio relogio(hora, minuto, segundo);
    cin >> numeroAjustes;
	
	for (i = 0; i < numeroAjustes; i++) {
		cin >> incremento;
		if (incremento == "tic") { //tentei fazer switch, mas descobri que nao se pode usar string para case
			incrementoSegundo++;
		} else if (incremento == "tac") {
			incrementoMinuto++;
		} else {
			cout << "erro" << endl;
			numeroAjustes++;
		}
	}
	
	relogio.ajustar(incrementoHora, incrementoMinuto, incrementoSegundo);
	printf("%02d:%02d:%02d\n", relogio.getHora(), relogio.getMinuto(), relogio.getSegundo());
    return 0;
}
