/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   noeud.h
 * Author: etudiant
 *
 * Created on 23 mars 2021, 13:34
 */

#ifndef NOEUD_H
#define NOEUD_H
class Noeud
 {
 public:

   Noeud (TValeur valeur, Noeud* gauche = nullptr, Noeud* droite = nullptr, Noeud* parent = nullptr) : valeur (valeur), gauche (gauche), droite (droite), parent (parent) { }

   // Accesseurs

   Noeud*
   reqGauche () const
   {
     return gauche;
   }

   Noeud*
   reqDroite () const
   {
     return droite;
   }

   Noeud*
   reqParent () const
   {
     return parent;
   }

   const TValeur&
   reqValeur () const
   {
     return valeur;
   }

   // Méthodes d'appartenance parent-enfant

   bool
   estParentDe (const Noeud& autre) const
   {
     return (&autre == gauche) or (&autre == droite);
   }

   bool
   estEnfantDe (const Noeud& autre) const
   {
     return (&autre == parent);
   }

   bool
   estUneFeuille () const
   {
     return (gauche == nullptr) and (droite == nullptr);
   }

   bool
   estUneRacine () const
   {
     return parent == nullptr;
   }

   // Mutateur

   void
   asgParent (Noeud& nouveauParent)
   {
     parent = &nouveauParent;
   }

   void
   asgEnfant (Noeud& nouvelEnfant)
   {
     if (nouvelEnfant < *this) this->gauche = &nouvelEnfant;
     else this->droite = &nouvelEnfant;

   }

   void asgEnfantGauche(Noeud* noeud) {
       gauche = noeud ;
   }

   void asgEnfantDroite(Noeud* noeud) {
       droite = noeud ;
   }

   // Opérateurs de comparaison. TValeur doit supporter operator < et ==

   bool operator< (Noeud r) const
   {
     return valeur < r.valeur;
   }

   bool operator> (Noeud r) const
   {
     return r.valeur < valeur;
   }

   bool operator<= (Noeud r) const
   {
     return !(*this > r);
   }

   bool operator>= (Noeud r) const
   {
     return !(*this < r);
   }

   bool operator== (Noeud r) const
   {
     return (*this <= r) and (*this >= r);
   }

   bool operator!= (Noeud r) const
   {
     return !(*this == r);
   }




 private:
   TValeur valeur;
   Noeud* gauche;
   Noeud* droite;
   Noeud* parent;
 };



#endif /* NOEUD_H */

