
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

public:

    ArbreBinaire() : racine(nullptr) {}

    ArbreBinaire(const ArbreBinaire &source) : racine(nullptr) {
        if (!source.racine) return;

        std::queue<Noeud *> enAttente;
        Noeud *courant = source.racine;
        enAttente.push(courant);

        while (!enAttente.empty()) {
            courant = enAttente.front();
            enAttente.pop();
            if (courant->reqDroite()) enAttente.push(courant->reqDroite());
            if (courant->reqGauche()) enAttente.push(courant->reqGauche());
            inserer(courant->reqValeur());
        }
    }

    virtual
    ~ArbreBinaire() {
       detruireLeSousArbre(racine) ;
    }

    const ArbreBinaire& operator = (ArbreBinaire autre) {
        Noeud *temp = this->racine;
        this->racine = autre.racine;
        autre.racine = temp;
        return (*this);
    }

    void detruireLeSousArbre(Noeud *sousArbre) {
        if (!sousArbre) return ;

        std::queue<Noeud *> enAttente;
        Noeud *courant = sousArbre;
        enAttente.push(courant);

        while (!enAttente.empty()) {
            courant = enAttente.front();
            enAttente.pop();
            if (courant->reqDroite()) enAttente.push(courant->reqDroite());
            if (courant->reqGauche()) enAttente.push(courant->reqGauche());
            delete courant;
        }
    }

    void visiterParNiveau(void (*callback)(Noeud *)) {
        if (!racine) return;

        std::queue<Noeud *> enAttente;
        Noeud *courant = racine;
        enAttente.push(courant);

        while (!enAttente.empty()) {
            courant = enAttente.front();
            enAttente.pop();
            if (courant->reqDroite()) enAttente.push(courant->reqDroite());
            if (courant->reqGauche()) enAttente.push(courant->reqGauche());
            (*callback)(courant);
        }
    }

    Noeud *
    minimumDuSousArbre(Noeud *depart) const {
        Noeud *courant = depart;
        while (courant->reqGauche()) courant = courant->reqGauche();
        return courant;
    }

    Noeud *
    minimumArbre() const {
        if (!racine) return nullptr;
        return minimumDuSousArbre(racine);
    }

    Noeud *
    maximumDuSousArbre(Noeud *depart) const {
        Noeud *courant = depart;
        while (courant->reqDroite()) courant = courant->reqDroite();
        return courant;
    }

    Noeud *
    maximumArbre() const {
        if (!racine) return nullptr;
        return maximumDuSousArbre(racine);
    }

    bool leNoeudEstUnEnfantDeGauche(Noeud *noeud) {
        if (!noeud->reqParent()) return false;
        return ((noeud->reqParent()->reqGauche()) == noeud);
    }

    bool leNoeudEstUnEnfantDeDroite(Noeud *noeud) {
        if (!noeud->reqParent()) return false;
        return ((noeud->reqParent()->reqDroite()) == noeud);
    }

    Noeud *
    successeur(Noeud *courant) const {
        if (courant->reqDroite() != nullptr) return minimumDuSousArbre(courant->reqDroite());
        Noeud *suivant = courant->reqParent();
        while ((suivant != nullptr) and (courant == suivant->reqDroite())) {
            courant = suivant;
            suivant = suivant->reqParent();
        }
        return suivant;
    }

    const_iterator
    cdebut() const {
        return const_iterator(this, minimumArbre());
    }

    iterator
    debut() const {
        return iterator(minimumArbre());
    }

    const_iterator
    cfin() const {
        return const_iterator(this, nullptr);
    }

    iterator
    fin() const {
        return iterator(this, nullptr);
    }
    
    void visitePostOrdreDansLeSousArbre(Noeud* sousArbre, std::vector<TValeur>& resultat) const {
      if (!sousArbre) return ; 
      visitePostOrdreDansLeSousArbre(sousArbre->reqGauche (), resultat) ; 
      visitePostOrdreDansLeSousArbre(sousArbre->reqDroite (), resultat) ; 
      resultat.push_back(sousArbre->reqValeur ()) ; 
    }
    
    std::vector<TValeur>
    visitePostOrdre() const {
      std::vector<TValeur> v ; 
      visitePostOrdreDansLeSousArbre(racine, v) ; 
      return v ; 
    }
    
    void visitePreOrdreDansLeSousArbre(Noeud* sousArbre, std::vector<TValeur>& resultat) const {
      if (!sousArbre) return ; 
      resultat.push_back(sousArbre->reqValeur ()) ; 
      visitePreOrdreDansLeSousArbre(sousArbre->reqGauche (), resultat) ; 
      visitePreOrdreDansLeSousArbre(sousArbre->reqDroite (), resultat) ; 
    }
    
    std::vector<TValeur>
    visitePreOrdre() const {
      std::vector<TValeur> v ; 
      visitePreOrdreDansLeSousArbre(racine, v) ; 
      return v ; 
    }

    void
    visiteEnOrdreDansLeSousArbre(Noeud *sousArbre, std::vector<TValeur> &resultat) const {
        if (!sousArbre) return;
        visiteEnOrdreDansLeSousArbre(sousArbre->reqGauche(), resultat);
        resultat.push_back(sousArbre->reqValeur());
        visiteEnOrdreDansLeSousArbre(sousArbre->reqDroite(), resultat);
    }

    std::vector<TValeur>
    visiteEnOrdre() const {
        std::vector<TValeur> v;
        visiteEnOrdreDansLeSousArbre(racine, v);
        return v;
    }

    void
    insererDansLaFeuille(Noeud &noeud, Noeud *feuille) {
        noeud.asgParent(*feuille);
        feuille->asgEnfant(noeud);
    }

    void
    insererDansLeSousArbre(Noeud &noeud, Noeud *sousArbre) {
        Noeud *destination = (noeud < *sousArbre) ? sousArbre->reqGauche() : sousArbre->reqDroite();
        if (!destination) insererDansLaFeuille(noeud, sousArbre);
        else insererDansLeSousArbre(noeud, destination);
    }

    void
    inserer(const TValeur &val) {
        Noeud *nouveauNoeud = new Noeud(val);
        if (estVide()) racine = nouveauNoeud;
        else insererDansLeSousArbre(*nouveauNoeud, racine);
    }

    void effacerLeNoeud(Noeud *noeud) {
        Noeud *parent = noeud->reqParent();
        parent->asgEnfantGauche(nullptr) ;
        parent->asgEnfantDroite(nullptr);
        delete noeud;
    }

    void transplanter(Noeud *destination, Noeud *depart) {
        if (destination == racine) racine = depart ;
        else if (leNoeudEstUnEnfantDeGauche(destination)) destination->reqParent()->asgEnfantGauche(depart) ;
        else destination->reqParent()->asgEnfantDroite(depart) ;
        if (depart) depart->asgParent(*(destination->reqParent())) ;
    }


    void supprimer(iterator iter) {
        Noeud *courant = iter.reqCourant();
        if (!courant->reqGauche()) transplanter(courant, courant->reqDroite()) ;
        else if (!courant->reqDroite()) transplanter(courant, courant->reqGauche()) ;
        else {
            Noeud* succ = minimumDuSousArbre(courant->reqDroite()) ;
            if (!succ->estEnfantDe(*courant)) {
                transplanter(succ, succ->reqDroite()) ;
                succ->asgEnfantDroite(courant->reqDroite()) ;
                succ->reqDroite()->asgParent(*courant) ;
            }
            transplanter(courant, succ) ;
            succ->asgEnfantGauche(courant->reqGauche()) ;
            succ->reqGauche()->asgParent(*courant) ;
        }
        delete courant ; 
    }
    
    void rotationGaucheNoeud(Noeud* x) {
      if (!x->reqDroite()) throw std::logic_error("Rotation vers la gauche interdite: pas d'enfant à droite.") ; 
      
      Noeud* y = x->reqDroite () ; 
      y->asgParent ( *(x->reqParent ()) ) ; 
      racine = (y->reqParent() != nullptr) ? racine : y ;
      x->asgParent( *y ) ; 
      x->asgEnfantDroite(y->reqGauche ()) ; 
      y->reqGauche ()->asgParent (*x) ; 
      y->asgEnfantGauche (x) ; 
    }
    
    void rotationGauche(iterator iter) {
      rotationGaucheNoeud(iter.reqCourant()) ; 
    }
    
    void rotationDroiteNoeud(Noeud* y) {
      if (!y->reqGauche()) throw std::logic_error("Rotation vers la droite interdite: pas d'enfant à gauche.") ; 
      
      Noeud* x = y->reqGauche() ; 
      x->asgParent( *(y->reqParent()) ) ; 
      racine = (x->reqParent() != nullptr) ? racine : x ; 
      y->asgParent(*x) ; 
      y->asgEnfantGauche(x->reqDroite()) ; 
      x->reqDroite()->asgParent(*y) ; 
      x->asgEnfantDroite(y) ; 
    }
    
    void rotationDroite(iterator iter) {
      rotationDroiteNoeud(iter.reqCourant()) ; 
    }
    
    void rotationGaucheAutourDuSommet() {
      rotationGaucheNoeud(racine) ; 
    }
    
    void rotationDroiteAutourDuSommet() {
      rotationDroiteNoeud(racine) ; 
    }

    bool
    leSousArbreEstVide(Noeud *sousArbre) const {
        return !sousArbre;
    }

    bool
    estVide() const {
        return leSousArbreEstVide(racine);
    }

    iterator
    chercher(const TValeur &valeur) const {
        return chercherDansLeSousArbre(valeur, racine);
    }

    iterator
    chercherDansLeSousArbre(const TValeur &valeur, Noeud *debut) const {
        if (!debut) return fin();
        if (valeur == debut->reqValeur()) return iterator(this, debut);
        if (valeur < debut->reqValeur()) return chercherDansLeSousArbre(valeur, debut->reqGauche());
        return chercherDansLeSousArbre(valeur, debut->reqDroite());
    }

    bool
    lesSousArbresSontSimilaires(const Noeud *lhs, const Noeud *rhs) const {
        if (!(lhs and rhs)) return (!(lhs or rhs));
        return lesSousArbresSontSimilaires(lhs->reqGauche(), rhs->reqGauche()) and
               lesSousArbresSontSimilaires(lhs->reqDroite(), rhs->reqDroite());
    }

    bool
    estSimilaireA(const ArbreBinaire &autre) {
        return lesSousArbresSontSimilaires(this->racine, autre.racine);
    }

private:
    Noeud *racine;
};


#endif /* ARBREBINAIRE_H */

