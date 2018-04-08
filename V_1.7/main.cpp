#include "grman/grman.h"
#include <iostream>

#include "graph.h"
#include "menu.h"
#include "test.h"
#include <string>





int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du r�pertoire o� se trouvent les images � charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    //g.load_graph();
    g.make_example();
    Menu m;
    Thing t;

    bool principal= false;

    int i=0;

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
    while ( !key[KEY_ESC] )
    {
            m.update(g,principal);
            grman::mettre_a_jour();
            while( !key[KEY_TAB] && principal )
            {
                g.update();
                g.lancer_dyn();

                /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
                grman::mettre_a_jour();
            }
            principal=false;



    }

     grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


