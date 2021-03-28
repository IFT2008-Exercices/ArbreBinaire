/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   iterator.h
 * Author: etudiant
 *
 * Created on 23 mars 2021, 13:37
 */

#ifndef ITERATOR_H
#define ITERATOR_H

/**
 * @class base_const_iterator
 * 
 * Classe de base à-partir de laquelle on va dériver les itérateurs sur les 
 * arbres binaires de recherche.  Il s'agit ici d'une classe incluse dans la 
 * classe ArbreBinaire. 
 */

class base_const_iterator
{
public:

  // Constructeur
  base_const_iterator (const ArbreBinaire* arbre, Noeud* adresse) : arbre (arbre), courant (adresse) { }

  // Retourne l'adresse du noeud courant
  Noeud*
  reqCourant () const
  {
    return courant;
  }

  // Modifie l'adresse du noeud courant
  void
  asgCourant (Noeud* nouveau)
  {
    courant = nouveau;
  }

  // Retourne un pointeur constant à l'arbre visité
  const ArbreBinaire*
  reqArbre () const
  {
    return arbre;
  }

  // Retourne la valeur au noeud courant
  const TValeur& operator* () const
  {
    return courant->reqValeur ();
  }

  // Deux itérateur sont égaux si les noeuds visités ont la même adresse
  bool operator== (const base_const_iterator& r) const
  {
    return courant == r.courant;
  }

  // Inégalité
  bool operator!= (const base_const_iterator& r) const
  {
    return !(*this == r);
  }
  
private:
  /** Arbre visité */
  const ArbreBinaire *arbre;
  
  /** Adresse du noeud courant */ 
  Noeud* courant;
};

/**
 * @class inOrder_const_iterator
 * Classe représentant un itérateur constant qui visite un arbre binaire en ordre.
 * Dérivée de base_const_iterator
 */

class inOrder_const_iterator : public base_const_iterator
{
public:

  // Constructeur
  inOrder_const_iterator (const ArbreBinaire* arbre, Noeud* adresse) : base_const_iterator (arbre, adresse) { };

  // Opérateurs d'incérmentations:  utilisent le successeur de l'arbre visité
  
  inOrder_const_iterator operator++ ()
  {
    base_const_iterator::asgCourant (base_const_iterator::reqArbre () ->successeurEnOrdre (base_const_iterator::reqCourant ()));
    return *this;
  }

  inOrder_const_iterator operator++ (int)
  {
    Noeud* actuel = base_const_iterator::reqCourant ();
    base_const_iterator::asgCourant (base_const_iterator::reqArbre () ->successeurEnOrdre (base_const_iterator::reqCourant ()));
    return actuel;
  }

};

/**
 * @class inOrderIterator
 * 
 * Classe représentant un itérateur non-constant qui visite un arbre binaire en
 * ordre.
 * 
 * Dérivée de inOrder_const_iterator
 */

class inOrder_iterator : public inOrder_const_iterator
{
public:

  inOrder_iterator (const ArbreBinaire* arbre, Noeud* adresse) : inOrder_const_iterator (arbre, adresse) { }

  // Retourne une référence non-constante à la valeur du noeud courant
  
  TValeur& operator* ()
  {
    return inOrder_const_iterator::reqCourant ()->reqValeur ();
  }

};


/**
 * @class preOrdre_const_iterator
 * Classe représentant un itérateur constant qui visite un arbre binaire de 
 * recherche en préordre.
 * 
 * Dérivée de base_const_iterator
 */

class preOrdre_const_iterator : public base_const_iterator
{
public:

  preOrdre_const_iterator (const ArbreBinaire* arbre, Noeud* adresse) : base_const_iterator (arbre, adresse) { };

  // Opérateurs d'incrémentation: utilisent le successeur de l'arbre visité
  
  preOrdre_const_iterator operator++ ()
  {
    base_const_iterator::asgCourant (base_const_iterator::reqArbre () ->successeurPreOrdre (base_const_iterator::reqCourant ()));
    return *this;
  }

  preOrdre_const_iterator operator++ (int)
  {
    Noeud* actuel = base_const_iterator::reqCourant ();
    base_const_iterator::asgCourant (base_const_iterator::reqArbre () ->successeurPreOrdre (base_const_iterator::reqCourant ()));
    return actuel;
  }

};

/**
 * @class preOrdre_iterator
 * 
 * Classe représentant un itérateur non-constant qui visite en préordre un 
 * arbre binaire de recherche.
 * 
 * Dérivé de preOrdre_const_iterator
 */

class preOrdre_iterator : public preOrdre_const_iterator
{
public:

  preOrdre_iterator (const ArbreBinaire* arbre, Noeud* adresse) : preOrdre_const_iterator (arbre, adresse) { }

  //  Retourne une référence non-constante à la valeur du noeud visité
  
  TValeur& operator* ()
  {
    return preOrdre_const_iterator::reqCourant ()->reqValeur ();
  }

};



#endif /* ITERATOR_H */

