#include "disco.h"
disco::disco(int tam) {
	tamanho = tam;
	próximo = nullptr;
}
int disco::getTamanho() const {
	return tamanho;
}
disco* disco::getProximo() const {
	return próximo;
}
void disco::setTamanho(int tam) {
	this->tamanho = tam;
}
void disco::setProximo(disco* pro) {
	this->próximo = pro;
}