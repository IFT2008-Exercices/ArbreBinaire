
/* 
 * File:   ArbreBinaire.h
 * Author: Pascal Charpentier
 *
 * Created on 16 mars 2021, 11:03
 */

#ifndef ARBREBINAIRE_H
#define ARBREBINAIRE_H

#include <queue>

template<typename TValeur>
class ArbreBinaire {

	private:

		#include "noeud.h"

	public:

		#include "iterator.h"

		ArbreBinaire() : racine(nullptr) {}

		ArbreBinaire(const ArbreBinaire& source) : racine(nullptr) {
			if (source.racine==nullptr) {
				return;
			}

			std::queue<Noeud*> enAttente;
			Noeud* courant = source.racine;
			enAttente.push(courant);

			while (!enAttente.empty()) {
				courant = enAttente.front();
				enAttente.pop();
				if (courant->reqDroite()) {
					enAttente.push(courant->reqDroite());
				}
				if (courant->reqGauche()) {
					enAttente.push(courant->reqGauche());
				}
				inserer(courant->reqValeur());
			}
		}

		virtual ~ArbreBinaire() {
			Noeud* courant = minimumArbre();
			while (courant!=nullptr) {
				Noeud* suivant = successeur(courant);
				delete courant;
				courant = suivant;
			}
		}

		const ArbreBinaire& operator=(ArbreBinaire autre) {
			Noeud* temp = this->racine;
			this->racine = autre.racine;
			autre.racine = temp;
			return *this;
		}

		void visiterParNiveau(void (* callback)(Noeud*)) {
			if (racine==nullptr) {
				return;
			}

			std::queue<Noeud*> enAttente;
			Noeud* courant = racine;
			enAttente.push(courant);

			while (!enAttente.empty()) {
				courant = enAttente.front();
				enAttente.pop();
				if (courant->reqDroite()) {
					enAttente.push(courant->reqDroite());
				}
				if (courant->reqGauche()) {
					enAttente.push(courant->reqGauche());
				}
				(*callback)(courant);
			}
		}

		Noeud* minimumDuSousArbre(Noeud* depart) const {
			Noeud* courant = depart;
			while (courant->reqGauche()) {
				courant = courant->reqGauche();
			}
			return courant;
		}

		Noeud* minimumArbre() const {
			if (racine==nullptr) {
				return nullptr;
			}
			return minimumDuSousArbre(racine);
		}

		Noeud* maximumDuSousArbre(Noeud* depart) const {
			Noeud* courant = depart;
			while (courant->reqDroite()) {
				courant = courant->reqDroite();
			}
			return courant;
		}

		Noeud* maximumArbre() const {
			if (racine==nullptr) {
				return nullptr;
			}
			return maximumDuSousArbre(racine);
		}

		Noeud* successeur(Noeud* courant) const {
			if (courant->reqDroite()!=nullptr) {
				return minimumDuSousArbre(courant->reqDroite());
			}
			Noeud* suivant = courant->reqParent();
			while ((suivant!=nullptr) and (courant==suivant->reqDroite())) {
				courant = suivant;
				suivant = suivant->reqParent();
			}
			return suivant;
		}

		const_iterator cdebut() const {
			return const_iterator(this, minimumArbre());
		}

		iterator debut() const {
			return iterator(minimumArbre());
		}

		const_iterator cfin() const {
			return const_iterator(this, nullptr);
		}

		iterator fin() const {
			return iterator(this, nullptr);
		}

		void visiteEnOrdreDansLeSousArbre(Noeud* sousArbre, std::vector<TValeur>& resultat) const {
			if (sousArbre==nullptr) {
				return;
			}
			visiteEnOrdreDansLeSousArbre(sousArbre->reqGauche(), resultat);
			resultat.push_back(sousArbre->reqValeur());
			visiteEnOrdreDansLeSousArbre(sousArbre->reqDroite(), resultat);
		}

		std::vector<TValeur> visiteEnOrdre() const {
			std::vector<TValeur> v;
			visiteEnOrdreDansLeSousArbre(racine, v);
			return v;
		}

		void insererDansLaFeuille(Noeud& noeud, Noeud* feuille) {
			noeud.asgParent(*feuille);
			feuille->asgEnfant(noeud);
		}

		void insererDansLeSousArbre(Noeud& noeud, Noeud* sousArbre) {
			Noeud* destination = (noeud < *sousArbre) ? sousArbre->reqGauche() : sousArbre->reqDroite();
			if (!destination) {
				insererDansLaFeuille(noeud, sousArbre);
			} else {
				insererDansLeSousArbre(noeud, destination);
			}
		}

		void inserer(const TValeur& val) {
			auto nouveauNoeud = new Noeud(val);
			if (estVide()) {
				racine = nouveauNoeud;
			} else {
				insererDansLeSousArbre(*nouveauNoeud, racine);
			}
		}

		void supprimer(Noeud* noeud) {
			// TODO
		}

		bool leSousArbreEstVide(Noeud* sousArbre) const {
			return sousArbre==nullptr;
		}

		bool estVide() const {
			return leSousArbreEstVide(racine);
		}

		const_iterator chercher(const TValeur& valeur) const {
			return chercherDansLeSousArbre(valeur, racine);
		}

		const_iterator chercherDansLeSousArbre(const TValeur& valeur, Noeud* debut) const {
			if (debut==nullptr) {
				return cfin();
			}
			if (valeur==debut->reqValeur()) {
				return const_iterator(this, debut);
			}
			if (valeur < debut->reqValeur()) {
				return chercherDansLeSousArbre(valeur, debut->reqGauche());
			}
			return chercherDansLeSousArbre(valeur, debut->reqDroite());
		}

		bool lesSousArbresSontSimilaires(const Noeud* lhs, const Noeud* rhs) const {
			if (!(lhs and rhs)) {
				return (!(lhs or rhs));
			}
			return lesSousArbresSontSimilaires(lhs->reqGauche(), rhs->reqGauche())
				and lesSousArbresSontSimilaires(lhs->reqDroite(), rhs->reqDroite());
		}

		bool estSimilaireA(const ArbreBinaire& autre) {
			return lesSousArbresSontSimilaires(this->racine, autre.racine);
		}

	private:
		Noeud* racine;
};

#endif

