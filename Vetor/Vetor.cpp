//Vetores no espaco (apenas coordenadas x, y, z), visto que acima de tridimensional nao e muito comum
//para fazer soma e subtracao no plano, basta desconsiderar valores de z
//produto vetorial nao faz sentido para um plano e provavelmente para vetores mais que tridimensionais

#include <iostream>

using namespace std;

class Vetor {
	private:
		float coordenada[3];

	public:
		Vetor();
		Vetor(float *);
		void setCoordenada(float *);
		float * getCoordenada();
		void mostraCoordenadas();
		Vetor operator + (Vetor);
		Vetor operator - (Vetor);
		Vetor operator * (Vetor);	//multiplicacao propriamente dita nao existe, o operador foi aproveitado para produto vetorial
		//divisao nao existe
};

Vetor::Vetor() {

}

Vetor::Vetor(float * coordenada) {
	setCoordenada(coordenada);

}

void Vetor::setCoordenada(float * coordenada) {
	this->coordenada[0] = *coordenada;
	this->coordenada[1] = *(coordenada+1);
	this->coordenada[2] = *(coordenada+2);
}

float * Vetor::getCoordenada() {
	return this->coordenada;
}

void Vetor::mostraCoordenadas() {
	cout << this->coordenada[0] << ", " << this->coordenada[1] << ", " << this->coordenada[2] << endl;
}

Vetor Vetor::operator + (Vetor vetor2) {
	float * coordenadaVetorB;
	coordenadaVetorB = vetor2.getCoordenada();

	float coordenadaB[3];
	coordenadaB[0] = *coordenadaVetorB;
	coordenadaB[1] = *(coordenadaVetorB+1);
	coordenadaB[2] = *(coordenadaVetorB+2);

	float coordenadaResultado[3];
	coordenadaResultado[0] = this->coordenada[0] + coordenadaB[0];
	coordenadaResultado[1] = this->coordenada[1] + coordenadaB[1];
	coordenadaResultado[2] = this->coordenada[2] + coordenadaB[2];

	Vetor resultado;
	resultado.setCoordenada(coordenadaResultado);
	coordenadaVetorB = NULL;
	delete coordenadaVetorB;
	return resultado;
}

Vetor Vetor::operator - (Vetor vetor2) {
	float * coordenadaVetorB;
	coordenadaVetorB = vetor2.getCoordenada();

	float coordenadaB[3];
	coordenadaB[0] = *coordenadaVetorB;
	coordenadaB[1] = *(coordenadaVetorB+1);
	coordenadaB[2] = *(coordenadaVetorB+2);

	float coordenadaResultado[3];
	coordenadaResultado[0] = this->coordenada[0] - coordenadaB[0];
	coordenadaResultado[1] = this->coordenada[1] - coordenadaB[1];
	coordenadaResultado[2] = this->coordenada[2] - coordenadaB[2];

	Vetor resultado;
	resultado.setCoordenada(coordenadaResultado);
	coordenadaVetorB = NULL;
	delete coordenadaVetorB;
	return resultado;
}

Vetor Vetor::operator * (Vetor vetor2) {
	/*
	o produto vetorial pode servir para formar uma base, ortonormal ou nao
	gera um vetor ortogonal aos outros dois
	|a11 a12 a13| a11 a12
	|a21 a22 a23| a21 a22
	|a31 a32 a33| a31 a32
			. . .

	| i   j  k | i  j
	|a0  a1  a2| a0 a1
	|b0  b1  b2| b0 b1

	multiplicacoes de diagonal. Da esquerda para direita mantem sinal, da direita para esquerda inverte sinal final (regra de Sarrus)
	
	resulta em (x)i, (y)j, (z)k, que sao as coordenadas do vetor gerado
	
	podem ser usadas outras regras, mas essa consegue ser mais intuitiva
	*/
	float * coordenadaVetorB;
	coordenadaVetorB = vetor2.getCoordenada();
	float iDireita, iEsquerda;
	float jDireita, jEsquerda;
	float kDireita, kEsquerda;

	float coordenadaB[3];
	coordenadaB[0] = *coordenadaVetorB;
	coordenadaB[1] = *(coordenadaVetorB+1);
	coordenadaB[2] = *(coordenadaVetorB+2);

	iDireita = this->coordenada[1] * coordenadaB[2];
	jDireita = this->coordenada[2] * coordenadaB[0];
	kDireita = this->coordenada[0] * coordenadaB[1];

	kEsquerda = (this->coordenada[1] * coordenadaB[0]) * -1;
	iEsquerda = (this->coordenada[2] * coordenadaB[1]) * -1;
	jEsquerda = (this->coordenada[0] * coordenadaB[2]) * -1;

	float coordenadaResultado[3];
	coordenadaResultado[0] = iDireita + iEsquerda;
	coordenadaResultado[1] = jDireita + jEsquerda;
	coordenadaResultado[2] = kDireita + kEsquerda;

	Vetor resultado;
	resultado.setCoordenada(coordenadaResultado);
	coordenadaVetorB = NULL;
	delete coordenadaVetorB;
	return resultado;
}

int main() {
	float coordenadaEntrada[3];
	coordenadaEntrada[0] = coordenadaEntrada[1] = coordenadaEntrada[2] = 0;

	cin >> coordenadaEntrada[0] >> coordenadaEntrada[1] >> coordenadaEntrada[2];
	cout << endl;
	Vetor vetor1 = Vetor(coordenadaEntrada);

	coordenadaEntrada[0] = coordenadaEntrada[1] = coordenadaEntrada[2] = 0;

	cin >> coordenadaEntrada[0] >> coordenadaEntrada[1] >> coordenadaEntrada[2];
	cout << endl;
	Vetor vetor2 = Vetor(coordenadaEntrada);

	//Soma
	Vetor soma;
	soma = vetor1 + vetor2;
	soma.mostraCoordenadas();

	//Subtracao
	Vetor subtracao;
	subtracao = vetor1 - vetor2;
	subtracao.mostraCoordenadas();

	//Produto vetorial
	Vetor produtoVetorial;	//na pratica eh o produto vetorial
	produtoVetorial = vetor1 * vetor2;
	produtoVetorial.mostraCoordenadas();
}
