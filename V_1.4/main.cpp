#include "grman/grman.h"
#include <iostream>

#include "graph.h"
#include "menu.h"
#include "test.h"
#include <string>

#include <winalleg.h>



int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
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
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {

//
//
//        while( !key[KEY_ASTERISK] && !principal )
//        {
//            m.update(g,principal);
//            grman::mettre_a_jour();
//
//            std::string graphe;
//
//        }



        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        //m.update();
        //t.update();
        g.update();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();

        rest(100);

        if(i>=1)

        if( key[KEY_0_PAD] ){ g.show_vertex_edges(0); if(key[KEY_F]){g.del_vertex(0); rest(1000);} }
        if( key[KEY_1_PAD] ){ g.show_vertex_edges(1); if(key[KEY_F]){g.del_vertex(1); rest(1000);} }
        if( key[KEY_2_PAD] ){ g.show_vertex_edges(2); if(key[KEY_F]){g.del_vertex(2); rest(1000);} }
        if( key[KEY_3_PAD] ){ g.show_vertex_edges(3); if(key[KEY_F]){g.del_vertex(3); rest(1000);} }
        if( key[KEY_4_PAD] ){ g.show_vertex_edges(4); if(key[KEY_F]){g.del_vertex(4); rest(1000);} }
        if( key[KEY_5_PAD] ){ g.show_vertex_edges(5); if(key[KEY_F]){g.del_vertex(5); rest(1000);} }
        if( key[KEY_6_PAD] ){ g.show_vertex_edges(6); if(key[KEY_F]){g.del_vertex(6); rest(1000);} }
        if( key[KEY_7_PAD] ){ g.show_vertex_edges(7); if(key[KEY_F]){g.del_vertex(7); rest(1000);} }
        if( key[KEY_W] ) {g.del_edge(0); rest(1000); }
        if( key[KEY_Z] ) {g.del_edge(1); rest(1000); }
        if( key[KEY_E] ) {g.del_edge(2); rest(1000); }
        if( key[KEY_R] ) {g.del_edge(3); rest(1000); }
        if( key[KEY_T] ) {g.del_edge(4); rest(1000); }
        if( key[KEY_Y] ) {g.del_edge(5); rest(1000); }

        //if(i>=1)g.del_edge(0);

        //if(i<4) g.del_vertex(5);
        //rest(5000);
        i++;

    }

    g.save_graph();



    grman::fermer_allegro();

    //if(i !=1) {g.save_graph(); i=1;}

    return 0;
}
END_OF_MAIN();


