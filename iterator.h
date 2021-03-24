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

 class const_iterator
  {
  public:

    const_iterator (const ArbreBinaire *arbre, Noeud* adresse) : arbre (arbre), courant (adresse) { }

    Noeud*
    reqCourant () const
    {
      return courant;
    }

    const TValeur& operator* () const
    {
      return courant->reqValeur ();
    }

    const_iterator operator++ ()
    {
      courant = arbre->successeur (courant);
      return *this;
    }

    const_iterator operator++ (int)
    {
      Noeud* actuel = courant;
      courant = arbre->successeur (courant);
      return actuel;
    }

    bool operator== (const const_iterator& r) const
    {
      return courant == r.courant;
    }

    bool operator!= (const const_iterator& r) const
    {
      return !(*this == r);
    }


  private:
    const ArbreBinaire *arbre;
    Noeud* courant;
  };

  class iterator : public const_iterator
  {
  public:

    iterator (ArbreBinaire arbre, Noeud* adresse) : const_iterator (arbre, adresse) { }

    TValeur& operator* ()
    {
      return const_iterator::reqCourant ()->reqValeur ();
    }

  };


#endif /* ITERATOR_H */

