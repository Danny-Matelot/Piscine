#include "grman/grman.h"
#include <iostream>

#include "graph.h"
#include "menu.h"
#include "test.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    g.load_graph();
    //g.make_example();
    Menu m;
    Thing t;

    int i=0;

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        //m.update();
        //t.update();
        g.update();

        //std::cout<< "test"<<std::endl;

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();



    }



    grman::fermer_allegro();

    if(i !=1) {g.save_graph(); i=1;}

    return 0;
}
END_OF_MAIN();


