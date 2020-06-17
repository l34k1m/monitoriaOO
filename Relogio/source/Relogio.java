import java.util.Scanner;


class Relogio { //para manter duas classes no mesmo arquivo, nao deve ser declarada public

	public int hora;
	public int minuto;
	public int segundo;
	
	public Relogio(int hora, int minuto, int segundo) {
		setSegundo(segundo);
		setMinuto(minuto);
		setHora(hora);
	}
	
	public int getHora() {
		return hora;
	}

	public void setHora(int hora) {
		this.hora = hora;
	}

	public int getMinuto() {
		return minuto;
	}

	public void setMinuto(int minuto) {
		this.minuto = minuto;
	}

	public int getSegundo() {
		return segundo;
	}

	public void setSegundo(int segundo) {
		this.segundo = segundo;
	}

	public void ajustaRelogio(int incrementoHora, int incrementoMinuto, int incrementoSegundo) {
		int segundoAtual = incrementoSegundo + this.getSegundo();
		if (segundoAtual>59) {
			int minutoAdicional = (int) segundoAtual/60;
			incrementoMinuto+= minutoAdicional;
		}
		segundoAtual = segundoAtual % 60;
		this.setSegundo(segundoAtual);
		
		int minutoAtual = incrementoMinuto + this.getMinuto();
		if (minutoAtual>59) {
			int horaAdicional = (int) minutoAtual/60;
				incrementoHora+= horaAdicional;
		}
		minutoAtual = minutoAtual % 60;
		this.setMinuto(minutoAtual);

		int horaAtual = (incrementoHora + this.getHora()) % 24;
			this.setHora(horaAtual);
			
	}
	
	//public void alteraSegundo(int incrementoSegundo) {
	//}
	//public void alteraHora(int incrementoMinuto) {
	//}
	//public void alteraMinuto(int incrementoHora) {
	//}'
	

	public static void main(String[] args) {

		int hora, minuto, segundo;
		int numeroAjustes, i;
		int incrementoHora = 0, incrementoMinuto = 0, incrementoSegundo = 0;
		String incremento;
		Scanner entrada = new Scanner(System.in);

		//System.out.println("Informe hora: ");
		hora = entrada.nextInt();
		//System.out.println("Informe minuto: ");
		minuto = entrada.nextInt();
		//System.out.println("Informe segundo: ");
		segundo = entrada.nextInt();
		//entrada.close();
		Relogio relogio = new Relogio(hora, minuto, segundo);
		
		//System.out.println("Informe numero de parametros de controle de tempo:");
		numeroAjustes = entrada.nextInt();

		for (i = 0; i < numeroAjustes; i++) {
			incremento = entrada.next();
			switch ( incremento ) {
			case "tic":
				incrementoSegundo++;
				break;
			case "tac":
				incrementoMinuto++;
				break;
			default:
				System.out.println("erro");
				numeroAjustes++;
			}
		}
		relogio.ajustaRelogio(incrementoHora, incrementoMinuto, incrementoSegundo);
		System.out.println(relogio.getHora() + ":" + relogio.getMinuto() + ":" + relogio.getSegundo());
	}
}
