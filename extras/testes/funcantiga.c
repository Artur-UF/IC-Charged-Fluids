//NPBC antigo

if(ds >= rrs){ // Verificando borda exterior
				// Verificando o o sinal de x
				if(todas[j].p[0] > 0 && todas[j].v[0] > 0){
					todas[j].v[0] *= -1.;
				}
				if(todas[j].p[0] < 0 && todas[j].v[0] < 0){
					todas[j].v[0] *= -1.;
				}
				
				// Verificando o sinal de y
				if(todas[j].p[1] > 0 && todas[j].v[1] > 0){
					todas[j].v[1] *= -1.;
				}
				if(todas[j].p[1] < 0 && todas[j].v[1] < 0){
					todas[j].v[1] *= -1.;
				}
				
				// Verificando o sinal de z
				if(todas[j].p[2] > 0 && todas[j].v[2] > 0){
					todas[j].v[2] *= -1.;
				}
				if(todas[j].p[2] < 0 && todas[j].v[2] < 0){
					todas[j].v[2] *= -1.;
				}
			}
			if(ds <= rri){ // Verificando borda interior
				// Verificando o o sinal de x
				if(todas[j].p[0] > 0 && todas[j].v[0] < 0){
					todas[j].v[0] *= -1.;
				}
				if(todas[j].p[0] < 0 && todas[j].v[0] > 0){
					todas[j].v[0] *= -1.;
				}
				
				// Verificando o sinal de y
				if(todas[j].p[1] > 0 && todas[j].v[1] < 0){
					todas[j].v[1] *= -1.;
				}
				if(todas[j].p[1] < 0 && todas[j].v[1] > 0){
					todas[j].v[1] *= -1.;
				}
				
				// Verificando o sinal de z
				if(todas[j].p[2] > 0 && todas[j].v[2] < 0){
					todas[j].v[2] *= -1.;
				}
				if(todas[j].p[2] < 0 && todas[j].v[2] > 0){
					todas[j].v[2] *= -1.;
				}
			}
