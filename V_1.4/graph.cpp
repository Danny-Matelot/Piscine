#include "graph.h"

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;
    if( !vertex_deleted )
    {
        /// Copier la valeur locale de la donnée m_value vers le slider associé
        m_interface->m_slider_value.set_value(m_value);

        /// Copier la valeur locale de la donnée m_value vers le label sous le slider
        m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
    }

}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    if( !vertex_deleted )
    {
        /// Reprendre la valeur du slider dans la donnée m_value locale
        m_value = m_interface->m_slider_value.get_value();
    }
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);



}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(100,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908-20,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANC);


    /// TOOL BOX

        m_tool_box.add_child(m_but_addvert);
        m_but_addvert.set_frame(3,10, 98,40);
        m_but_addvert.set_bg_color(VERT);
        m_but_addvert.set_gravity_x(grman::GravityX::Center);
        m_but_addvert.add_child(m_txt_addvert);
        m_txt_addvert.set_message("ADD VERTEX");

        m_tool_box.add_child(m_but_addedge);
        m_but_addedge.set_frame(3,55, 98,40);
        m_but_addedge.set_bg_color(VERT);
        m_but_addvert.set_gravity_x(grman::GravityX::Center);
        m_but_addedge.add_child(m_txt_addedge);
        m_txt_addedge.set_message(" ADD EDGE");



        m_tool_box.add_child(m_but_delvert);
        m_but_delvert.set_frame(3,100, 98,40);
        m_but_delvert.set_bg_color(ROUGE);
        m_but_delvert.set_gravity_x(grman::GravityX::Center);
        m_but_delvert.add_child(m_txt_delvert);
        m_txt_delvert.set_message("DEL VERTEX");

        m_tool_box.add_child(m_but_deledge);
        m_but_deledge.set_frame(3,145, 98,40);
        m_but_deledge.set_bg_color(ROUGE);
        m_but_deledge.set_gravity_x(grman::GravityX::Center);
        m_but_deledge.add_child(m_txt_deledge);
        m_txt_deledge.set_message("DEL EDGE");


        m_tool_box.add_child(m_but_kosaraju);
        m_but_kosaraju.set_frame(3,190, 98,40);
        m_but_kosaraju.set_bg_color(BLEU);
        m_but_kosaraju.set_gravity_x(grman::GravityX::Center);
        m_but_kosaraju.add_child(m_txt_kosaraju);
        m_txt_kosaraju.set_message("KOSARAJU");

        m_tool_box.add_child(m_but_konnexite);
        m_but_konnexite.set_frame(3,235, 98,40);
        m_but_konnexite.set_bg_color(BLEU);
        m_but_konnexite.set_gravity_x(grman::GravityX::Center);
        m_but_konnexite.add_child(m_txt_konnexite);
        m_txt_konnexite.set_message("K CONEXITE");


}


/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex(0, 30.0, 200, 100, "clown1.jpg");
    add_interfaced_vertex(1, 60.0, 400, 100, "clown2.jpg");
    add_interfaced_vertex(2,  50.0, 200, 300, "clown3.jpg");
    add_interfaced_vertex(3,  0.0, 400, 300, "clown4.jpg");
    add_interfaced_vertex(4,  100.0, 600, 300, "clown5.jpg");
    add_interfaced_vertex(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg", 0);
    add_interfaced_vertex(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
    add_interfaced_vertex(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);

    /// Les arcs doivent être définis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    add_interfaced_edge(0, 1, 2, 50.0);
    add_interfaced_edge(1, 0, 1, 50.0);
    add_interfaced_edge(2, 1, 3, 75.0);
    add_interfaced_edge(3, 4, 1, 25.0);
    add_interfaced_edge(4, 6, 3, 25.0);
    add_interfaced_edge(5, 7, 3, 25.0);
    add_interfaced_edge(6, 3, 4, 0.0);
    add_interfaced_edge(7, 2, 0, 100.0);
    add_interfaced_edge(8, 5, 2, 20.0);
    add_interfaced_edge(9, 3, 7, 80.0);
}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();
    this->use_toolbox();

    for (auto &elt : m_vertices)
    {
         elt.second.post_update();
    }


    for (auto &elt : m_edges)
    {
         elt.second.post_update();
    }


}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);

    m_edges[idx] = Edge(weight, ei);



    // Label de visualisation d'index du sommet dans une boite
    m_edges[idx].m_interface->m_top_edge.add_child( m_edges[idx].m_interface->m_box_label_idx );
    m_edges[idx].m_interface->m_box_label_idx.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);
    m_edges[idx].m_interface->m_box_label_idx.set_dim(20,12);
//    m_edges[idx].m_interface->m_box_label_idx.set_bg_color(GRIS);

    m_edges[idx].m_interface->m_box_label_idx.add_child( m_edges[idx].m_interface->m_label_idx );
    m_edges[idx].m_interface->m_label_idx.set_message( std::to_string(idx) );


    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;
    m_vertices[id_vert1].m_eout.push_back(idx);
    m_vertices[id_vert2].m_ein.push_back(idx);
    m_vertices[id_vert1].m_out.push_back(id_vert2);
    m_vertices[id_vert2].m_in.push_back(id_vert1);

}

void Graph::save_graph()
{
    std::string name_file;
//    int choix;

    /// REQUEST NAME FILE TO SAVE
/*//
//    if (al_show_native_message_box(screen, "Choix du fichier de sauvegarde","Souhaitez vous nommer votre fichier de sauvegarde ?",
//     " Si oui, saisir dans la console. \n Si non, il sera sauvegardé sur le fichier ''auto_save'' "  )
//        std::cin>> name_file;
//        else name_file = "save";
//
//
*/

    std::cout<< "   Saisir le nom du fichier de sauvergarde que vous voulez donner"<<std::endl;
    std::cin>> name_file;
    name_file += ".txt";

    std::ofstream file_save( name_file.c_str(), std::ios::trunc );

    // 1st line file : order // 2nd line: number of edges
    file_save<< m_vertices.size() << std::endl<< m_edges.size()<<std::endl<<
      ""<< m_interface->m_top_box.get_posx() <<" " << m_interface->m_top_box.get_posy()<<" "<<
      " "<< m_interface->m_top_box.get_dimx()<<" " << m_interface->m_top_box.get_dimy()<<std::endl;
    // les dimensions pour le std::shared_ptr<GraphInterface> m_interface = nullptr;

    // insertion selon l'ordre des paramètres de la methode add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx)
    for ( unsigned int i = 0; i< m_vertices.size(); i++)
    {
        file_save<< i << " "<<  m_vertices[i].m_value << " " << m_vertices[i].m_interface->m_top_box.get_posx() <<
         " "<< m_vertices[i].m_interface->m_top_box.get_posy() << " " << m_vertices[i].m_interface->m_img.get_pic_name() <<
         " "<< m_vertices[i].m_interface->m_img.get_pic_idx() << std::endl;
    }

    // insertion selon l'ordre des paramètres de la methode add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
    for ( unsigned int i = 0; i< m_edges.size(); i++)
    {
        file_save<< i << " " << m_edges[i].m_from << " "<< m_edges[i].m_to << " "<< m_edges[i].m_weight<<std::endl;
    }

    std::cout<< "Sauvegarde du graphe effectuée !" <<std::endl;
}

using namespace std;

void Graph::load_graph()
{
    string name_file;

    cout << "  A partir de quel fichier voulez vous charger votre graphe ? \n\t Entrer le nom du fichier et son extension : ";
    cin>> name_file;

    ifstream ld_file( name_file.c_str(), ios::in );


    /// Traitement
    if(!ld_file.is_open()){ cout << " ERROR: can't open the save file"<<endl; }
    else
    {


        int ordre, nb_aretes;
        int vid, vvalue, vx, vy,vpic_id,eid,es1,es2,ew;
        string vpic_name;

        int x,y,w,h;

        ld_file>>ordre>>nb_aretes>>x>>y>>w>>h;

        m_interface = std::make_shared<GraphInterface>(x, y, w, h);

        for(int i = 0; i < ordre; i++)
        {
            ld_file>> vid>> vvalue>>vx>>vy>> vpic_name>>vpic_id;
            add_interfaced_vertex(vid, vvalue, vx, vy, vpic_name.c_str(), vpic_id);

        }
        for(int i = 0 ; i < nb_aretes ; i++)
        {
            ld_file>> eid>> es1>>es2>>ew;
            add_interfaced_edge(eid,es1,es2,ew);
        }

    }

}

/// Basé sur le code fourni sur campus

void Graph::del_edge_old(int eidx)
{
    if( (eidx <= m_edges.size() -1 ) && ( eidx >=0 ) )
    {if ( m_edges.size() > 0 ) {
                 /// référence vers le Edge à enlever

        std::cout <<  std::endl;

        Edge &remed=m_edges.at(eidx);

        std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;

        /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2




        std::cout <<" m_from : "<< m_vertices[remed.m_from].m_ein.size() << " " << m_vertices[remed.m_from].m_eout.size() << std::endl;
        std::cout <<" m_to   : "<<m_vertices[remed.m_to].m_ein.size() << " " << m_vertices[remed.m_to].m_eout.size() << std::endl;
        std::cout <<"   m_edges. size : "<< m_edges.size() << std::endl<< std::endl;



        /// test : on a bien des éléments interfacés

        if (m_interface && remed.m_interface)
        {
            m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
        }


        /// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !
        /// References sur les listes de edges des sommets from et to

        std::vector<int> &evefrom = m_vertices[remed.m_from].m_eout;
        std::vector<int> &eveto = m_vertices[remed.m_to].m_ein;
        evefrom.erase( std::remove( evefrom.begin(), evefrom.end(), eidx ), evefrom.end() );
        eveto.erase( std::remove( eveto.begin(), eveto.end(), eidx ), eveto.end() );

        /// POOUR DES QUESTIONS DE COMPATIBILITES
            /// on a aussi les sommets qui ont des vecteurs contenant l'id des sommets qui sont reliés à eux
            /// une fois l'arc supprimé, ont doit aussi effacer cette liaison
            /// c'est basiquement (simplement) la même chose qu'au dessus, et  même si on aurait pu accèder à ça grâce à l'intermédiaire
            /// de m_in[i].m_from , le travail en parallèle fait qu'il est bien plus simple d'écrire ces lignes de codes

//        std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
//        std::vector<int> &veto = m_vertices[remed.m_to].m_in;
//        vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
//        veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );



        std::vector<int> &entre_in   = m_vertices[m_edges[eidx].m_from].m_in;
        std::vector<int> &entre_out  = m_vertices[m_edges[eidx].m_from].m_out;
        std::vector<int> &sortie_in  = m_vertices[m_edges[eidx].m_to].m_in;
        std::vector<int> &sortie_out = m_vertices[m_edges[eidx].m_to].m_out;

        entre_in.erase( std::remove( entre_in.begin(), entre_in.end(), m_edges[eidx].m_to ), entre_in.end() );
        entre_out.erase( std::remove( entre_out.begin(), entre_out.end(), m_edges[eidx].m_to ), entre_out.end() );
        sortie_in.erase( std::remove( sortie_in.begin(), sortie_in.end(), m_edges[eidx].m_to ), sortie_in.end() );
        sortie_out.erase( std::remove( sortie_out.begin(), sortie_out.end(), m_edges[eidx].m_to ), sortie_out.end() );

        /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
        /// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
        /// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !

        m_edges.erase( eidx );

        /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
        std::cout << m_vertices[remed.m_from].m_ein.size() << " " << m_vertices[remed.m_from].m_eout.size() << std::endl;
        std::cout << m_vertices[remed.m_to].m_ein.size() << " " << m_vertices[remed.m_to].m_eout.size() << std::endl;
        std::cout << "size :" <<  m_edges.size() << std::endl;


        std::map<int, Edge>::iterator it = m_edges.begin(); // itérateur pour parcourir m_edges

        map<int, Edge> m_edges_ordre; // la nouvelle map qui elle aura des arrêtes numérotés correctement sans "trous"

        int compteur = 0;

        for( it = m_edges.begin() ; it != m_edges.end() ; ++it)
        {
            m_edges_ordre[compteur] = it->second; // le numéro compteur croissant prend la valeur équivalant à la même case dans l'ancienne map désordonnée
            compteur++;
        }

        m_edges = m_edges_ordre;// on MAJ l'ancienne map

        /// maintenant il faut dire aux sommets les nouveaux ids des edges/

        for(std::map<int, Vertex>::iterator i = m_vertices.begin() ; i != m_vertices.end() ; ++i)
        {
            i->second.m_ein.clear();
            i->second.m_eout.clear();
        }

        for( it = m_edges.begin() ; it != m_edges.end() ; ++it)
        {
            m_vertices[ it->second.m_from ].m_eout.push_back( it->first );
            m_vertices[ it->second.m_to ].m_ein.push_back( it->first );
        }

//        for( it = m_edges.begin() ; it != m_edges.end() ; ++it)
//        {
//            cout<<endl<<" Edge : "<<it->first<<endl;
//            cout << " s: "<< it->second.m_from<< " "<< m_vertices[ it->second.m_from ].m_eout[it->first ]<<endl;
//            cout << " s: "<< it->second.m_to  << " "<< m_vertices[ it->second.m_to ].m_ein[it->first]<<endl;
//        }

        for(map<int, Vertex>::iterator iterac = m_vertices.begin() ; iterac != m_vertices.end() ; ++iterac)
        {
            cout <<endl<< endl<< "   sommet : "<< iterac->first<< endl<< "      E:";
            for( vector<int>::iterator arete = iterac->second.m_ein.begin() ; arete != iterac->second.m_ein.end() ; ++arete )
            {
                cout<< " "<< *arete;
            }
            cout<<endl<< "      S:";
            for( vector<int>::iterator arete = iterac->second.m_out.begin() ; arete != iterac->second.m_out.end() ; ++arete )
            {
                cout<< " "<< *arete;
            }
        }



           // for( it = m_edges.begin() ; it != m_edges.end() ; ++it ){ std::cout << "CYCLE 2 id egde : " << it->first << std::endl; }
        std::cout<<std::endl;
        }else{ std::cout<< " ERROR: EDGE ID SUPERIOR TO NUMBER OF EDGE IN THIS GRAPH, C4N'T DELETE "<<std::endl; }

    }
    else{ std::cout<< " ERROR: EDGE ID SUPERIOR TO NUMBER OF EDGE IN THIS GRAPH, C4N'T DELETE "<<std::endl; }


}

void Graph::del_edge(int eidx)
{
    Edge &remed=m_edges.at(eidx);
//        std::vector<int> &entre_in   = m_vertices[remed.m_from].m_in;
//        std::vector<int> &entre_out  = m_vertices[remed.m_from].m_out;
//        std::vector<int> &sortie_in  = m_vertices[remed.m_to].m_in;
//        std::vector<int> &sortie_out = m_vertices[remed.m_to].m_out;

        std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;

    //if( (eidx <= m_edges.size()  ) && ( eidx >=0 ) )
    { //if ( m_edges.size() > 0 )
        {
                 /// référence vers le Edge à enlever

        std::cout <<  std::endl;


         /// test : on a bien des éléments interfacés

        if (m_interface && remed.m_interface)
        {
            m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
        }

        //if( m_edges.erase( eidx ) ==1 ) cout <<" EFFACE" <<endl;
        m_edges.erase( eidx );
        /// On supprime dans les sommets la présences de l'entrée et/ou sortie des ids edge

        for( map< int, Vertex>::iterator x = m_vertices.begin() ; x != m_vertices.end() ; ++x )
        {
            x->second.m_ein.erase( remove( x->second.m_ein.begin() , x->second.m_ein.end() , eidx ), x->second.m_ein.end() );
            x->second.m_eout.erase( remove( x->second.m_eout.begin() , x->second.m_eout.end() , eidx ), x->second.m_eout.end() );
        }
        //std::cout<<std::endl<< " putain de size 1.1 "<< m_edges.size()<<endl;

        /// POOUR DES QUESTIONS DE COMPATIBILITES
            /// on a aussi les sommets qui ont des vecteurs contenant l'id des sommets qui sont reliés à eux
            /// une fois l'arc supprimé, ont doit aussi effacer cette liaison
            /// c'est basiquement (simplement) la même chose qu'au dessus, et  même si on aurait pu accèder à ça grâce à l'intermédiaire
            /// de m_in[i].m_from , le travail en parallèle fait qu'il est bien plus simple d'écrire ces lignes de codes

            for( map< int, Vertex>::iterator x = m_vertices.begin() ; x != m_vertices.end() ; ++x )
        {
            x->second.m_in.erase( remove( x->second.m_in.begin() , x->second.m_in.end() , remed.m_from ), x->second.m_in.end() );
            x->second.m_out.erase( remove( x->second.m_out.begin() , x->second.m_out.end() , remed.m_to ), x->second.m_out.end() );
            x->second.m_in.erase( remove( x->second.m_in.begin() , x->second.m_in.end() , remed.m_to ), x->second.m_in.end() );
            x->second.m_out.erase( remove( x->second.m_out.begin() , x->second.m_out.end() , remed.m_from  ), x->second.m_out.end() );
        }


        /// FAit pour réorganiser la map et la runémérotant mais ça marche vraiment pas

/*
//        std::vector<int> &entre_in   = m_vertices[m_edges[eidx].m_from].m_in;
//        std::vector<int> &entre_out  = m_vertices[m_edges[eidx].m_from].m_out;
//        std::vector<int> &sortie_in  = m_vertices[m_edges[eidx].m_to].m_in;
////        std::vector<int> &sortie_out = m_vertices[m_edges[eidx].m_to].m_out;
//
//        entre_in.erase( std::remove( entre_in.begin(), entre_in.end(), m_edges[eidx].m_to ), entre_in.end() );
//        entre_out.erase( std::remove( entre_out.begin(), entre_out.end(), m_edges[eidx].m_to ), entre_out.end() );
//        sortie_in.erase( std::remove( sortie_in.begin(), sortie_in.end(), m_edges[eidx].m_to ), sortie_in.end() );
//        sortie_out.erase( std::remove( sortie_out.begin(), sortie_out.end(), m_edges[eidx].m_to ), sortie_out.end() );

//        std::cout<<std::endl<< " putain de size 2.2 "<< m_edges.size()<<endl;
//
//        /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
//        /// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
//        /// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
//
//
//        std::map<int, Edge>::iterator it = m_edges.begin(); // itérateur pour parcourir m_edges
//
//        map<int, Edge> m_edges_ordre; // la nouvelle map qui elle aura des arrêtes numérotés correctement sans "trous"
//
//        int compteur = 0;
//
//        for( auto& it : m_edges)
//        {
//            m_edges_ordre[compteur] = it.second; // le numéro compteur croissant prend la valeur équivalant à la même case dans l'ancienne map désordonnée
//            cout<< " copying it.first: "<< it.first<<  " to compteur "<< compteur << endl;
//            compteur++;
//        }
//
//        m_edges = m_edges_ordre;// on MAJ l'ancienne map
//
//        /// maintenant il faut dire aux sommets les nouveaux ids des edges/
//
//        for( map< int, Vertex>::iterator x = m_vertices.begin() ; x != m_vertices.end() ; ++x )
//        {
//            x->second.m_ein.clear();
//            x->second.m_eout.clear();
//        }
//
//        for( it = m_edges.begin() ; it != m_edges.end() ; ++it)
//        {
//            m_vertices[ it->second.m_from ].m_eout.push_back( it->first );
//            m_vertices[ it->second.m_to ].m_ein.push_back( it->first );
//        }
//
//         std::map< int, Vertex >::iterator blah;
//         for( blah = m_vertices.begin() ; blah != m_vertices.end() ; ++blah ){show_vertex_edges(blah->first);}
*/

        //std::cout<<std::endl<< " putain de size 3 "<< m_edges.size()<<endl;
        }//else{ std::cout<< " ERROR: EDGE ID SUPERIOR TO NUMBER OF EDGE IN THIS GRAPH, C4N'T DELETE "<<std::endl; }

    }
    //else{ std::cout<< " ERROR: EDGE ID SUPERIOR TO NUMBER OF EDGE IN THIS GRAPH, C4N'T DELETE "<<std::endl; }


}


void Graph::del_vertex_old(int v_id)
{


    /// référence vers le Edge à enlever

    std::cout <<std::endl<< " HELLO, on s'en va supprimer le sommet : "<< v_id << std::endl<<std::endl;

    vector<int> edge_list_removal;
    int arc_entrant =0;
    int arc_sortant = 0;

        std::cout <<std::endl<< "       les arcs entrants sont : ";
        for(vector<int>::iterator i = m_vertices[v_id].m_ein.begin() ; i != m_vertices[v_id].m_ein.end() ; ++i )
        {
            cout<< " " << *i ;
            edge_list_removal.push_back(*i);
            arc_entrant++;
        }
        cout<< std::endl<<std::endl;

        std::cout <<std::endl<< "       les arcs sortants sont : ";
        for(vector<int>::iterator i = m_vertices[v_id].m_eout.begin() ; i != m_vertices[v_id].m_eout.end() ; ++i )
        {
            cout<< " " << *i ;
            edge_list_removal.push_back(*i);
            arc_sortant++;
        }
        cout<< std::endl<<std::endl;

//        cout<< " arc premier à retirer : ";
//        for(vector<int>::iterator i = edge_list_removal.begin() ; i != edge_list_removal.end() ; ++i )
//        {
//            cout<<   *i << " ";
//        }
//        cout << endl << endl;

    ///Maintenant on retire les arc qui vont/viennet de ce sommet ( ils s'auto retireront de la liste des autres sommets)

/*
//    for( int i = 0 ; i < m_vertices[v_id].m_ein.size() ; i++ )
//    {
//        std::cout<< " On supprime l'arc entrant : " << m_vertices[v_id].m_ein[i] << std::endl;
//        del_edge( m_vertices[v_id].m_ein[i] );
//    }
//
//    for( int i = 0 ; i < m_vertices[v_id].m_eout.size() ; i++ )
//    {
//        std::cout<< " On supprime l'arc sortant : " << m_vertices[v_id].m_eout[i] << std::endl;
//        del_edge( m_vertices[v_id].m_eout[i] );
//    }

//    for(vector<int>::iterator i = m_vertices[v_id].m_ein.begin() ; i != m_vertices[v_id].m_ein.end() ; ++i)
//    {
//        //if(!m_vertices[v_id].m_ein.empty() )
//        {
//            std::cout<< " On supprime l'arc entrant : " << *i << std::endl;
//            del_edge( *i );
//        }
//    }
//
//    for( vector<int>::iterator i = m_vertices[v_id].m_eout.begin() ; i != m_vertices[v_id].m_eout.end() ; ++i )
//    {
//        //if( !m_vertices[v_id].m_eout.empty() )
//        {
//            std::cout<< " On supprime l'arc sortant : " << *i << std::endl;
//            del_edge( *i );
//        }
//    }
*/

        int test = m_vertices[v_id].m_ein.size() + m_vertices[v_id].m_eout.size();

/*        for(int i=0; i < test ; i++ )
        {

//            if( !m_vertices[v_id].m_ein.empty() )
//            {
//                for( vector<int>::iterator i = m_vertices[v_id].m_ein.begin() ; i != m_vertices[v_id].m_ein.end() ; ++i )
//                {
//                    {
//                        std::cout<< " On supprime l'arc  : " << *i << std::endl;
//                        del_edge( *i );
//                        this->update();
//                        grman::mettre_a_jour();
//                        fill_edge_list(edge_list_removal,v_id);
//                    }
//                }
//            }
//            if( !m_vertices[v_id].m_eout.empty() )
//            {
//                for( vector<int>::iterator i = m_vertices[v_id].m_eout.begin() ; i != m_vertices[v_id].m_eout.end() ; ++i )
//                {
//                    {
//                        std::cout<< " On supprime l'arc  : " << *i << std::endl;
//                        del_edge( *i );
//                        this->update();
//                        grman::mettre_a_jour();
//                        fill_edge_list(edge_list_removal,v_id);
//                    }
//                }
//            }


            if( !m_vertices[v_id].m_ein.empty() )
            {
                for( auto i = 0 ; i < arc_entrant ; i++ )
                {
                    {
                        //std::cout<< " On supprime l'arc  : " << *i << std::endl;
                        del_edge( i );
                        this->update();
                        grman::mettre_a_jour();
                        fill_edge_list(edge_list_removal,v_id);
                    }
                }
            }
            if( !m_vertices[v_id].m_eout.empty() )
            {
                for( auto i = 0 ; i < arc_sortant ; i++ )
                {
                    {
                        //std::cout<< " On supprime l'arc  : " << *i << std::endl;
                        del_edge( i );
                        this->update();
                        grman::mettre_a_jour();
                        fill_edge_list(edge_list_removal,v_id);
                    }
                }
            }

        }
*/
/*        while(test > 0 )
        {
            cout << "test = "<<test <<endl;

            int nb_ope = 0; //un compteur qui compte le nb d'opé, dont test sera prélevé, ce qui permet de savoir combien d'arete il reste

            if( !m_vertices[v_id].m_ein.empty() )
            {

                int i = m_vertices[v_id].m_ein[0];
                    {
                        std::cout<< " On supprime l'arc  : " << i << std::endl;
                        del_edge( i );
                        this->update();
                        grman::mettre_a_jour();
                        nb_ope++;
                        cout << "nb ope +1 = "<< nb_ope<<endl;
                    }

            }else { cout<< "    m_vertices[v_id].m_ein.empty() "<<endl; }

            if( !m_vertices[v_id].m_eout.empty() )
            {
                int i = m_vertices[v_id].m_eout[0];
                    {
                        std::cout<< " On supprime l'arc  : " << i << std::endl;
                        del_edge( i );
                        this->update();
                        grman::mettre_a_jour();
                        nb_ope++;
                        cout << "nb ope +1 = "<< nb_ope<<endl;
                    }
            }else { cout<< "    m_vertices[v_id].m_eout.empty() "<<endl; }

            test = test- nb_ope;

        }

    cout<< " out the loop, test= "<<test<<endl;
*/






    Vertex &delver=m_vertices.at(v_id);
    /// si les interfaces sont communes
    if( m_interface && delver.m_interface ) m_interface->m_main_box.remove_child( delver.m_interface->m_top_box );
    /// on retire la parenté entre l'interface du vertex et du graphe

    m_vertices.erase( v_id ); // on enlève le sommet de la liste

    ///Le petit ajout correcteur pour renuméroter la map

    std::map<int, Vertex>::iterator it = m_vertices.begin(); // itérateur pour parcourir m_edges

    map<int, Vertex> m_vertices_ordre; // la nouvelle map qui elle aura des arrêtes numérotés correctement sans "trous"

    int compteur = 0;

    for( it = m_vertices.begin() ; it != m_vertices.end() ; ++it)
    {
        m_vertices_ordre[compteur] = it->second; // le numéro compteur croissant prend la valeur équivalant à la même case dans l'ancienne map désordonnée
        compteur++;
    }

    m_vertices = m_vertices_ordre;// on MAJ l'ancienne map

       // for( it = m_vertices.begin() ; it != m_vertices.end() ; ++it ){ std::cout << "CYCLE 2 id vertex : " << it->first << std::endl; }
        std::cout<<std::endl;

}

/// Adapté du code fourni sur les edges
void Graph::del_vertex(int v_id)
{

    /// référence vers le Edge à enlever

    std::cout <<std::endl<< " HELLO, on s'en va supprimer le sommet : "<< v_id << std::endl<<std::endl;


        std::cout <<std::endl<< "       les arcs entrants sont : ";
        for(vector<int>::iterator i = m_vertices[v_id].m_ein.begin() ; i != m_vertices[v_id].m_ein.end() ; ++i )
        {
            cout<< " " << *i ;
        }
        cout<< std::endl<<std::endl;

        std::cout <<std::endl<< "       les arcs sortants sont : ";
        for(vector<int>::iterator i = m_vertices[v_id].m_eout.begin() ; i != m_vertices[v_id].m_eout.end() ; ++i )
        {
            cout<< " " << *i ;
        }
        cout<< std::endl<<std::endl;




    ///Maintenant on retire les arc qui vont/viennet de ce sommet ( ils s'auto retireront de la liste des autres sommets)

    auto sizein = m_vertices[v_id].m_ein.size() ;
    auto sizeout =m_vertices[v_id].m_eout.size() ;

    for(auto nb_in =0 ; nb_in < sizein ; nb_in++  )
    {
        vector<int>::iterator x = m_vertices[v_id].m_ein.begin();
        del_edge( *x );
        cout<< " size après une supp arc" <<" "<< m_edges.size();
    }
    for(auto nb_out =0 ; nb_out < sizeout ; nb_out++  )
    {
        vector<int>::iterator x = m_vertices[v_id].m_eout.begin();
        del_edge( *x );
        cout<< " size après une supp arc" <<" "<< m_edges.size()<<endl;
    }


    Vertex &delver=m_vertices.at(v_id);
    /// si les interfaces sont communes
    if( m_interface && delver.m_interface ) m_interface->m_main_box.remove_child( delver.m_interface->m_top_box );
    /// on retire la parenté entre l'interface du vertex et du graphe



    m_vertices.erase( v_id ); // on enlève le sommet de la liste

            /// FAit pour réorganiser la map et la runémérotant mais ça marche vraiment pas
/*
//    ///Le petit ajout correcteur pour renuméroter la map
//
//    std::map<int, Vertex>::iterator it = m_vertices.begin(); // itérateur pour parcourir m_edges
//
//    map<int, Vertex> m_vertices_ordre; // la nouvelle map qui elle aura des arrêtes numérotés correctement sans "trous"
//
//    int compteur = 0;
//
//    for( it = m_vertices.begin() ; it != m_vertices.end() ; ++it)
//    {
//        m_vertices_ordre[compteur] = it->second; // le numéro compteur croissant prend la valeur équivalant à la même case dans l'ancienne map désordonnée
//        compteur++;
//    }
//
//    m_vertices = m_vertices_ordre;// on MAJ l'ancienne map
*/
            std::cout <<std::endl<< "   Sommet : "<< v_id <<" supprime"<< std::endl<<std::endl;
}
/// fonction qui sert àvoir si l'une des fonctions de la toolbox est demandée
void Graph::use_toolbox()
{
    // LES DEL
    if(m_interface->m_but_delvert.clicked())
    {
        int sommet;
        cout<< " Quel sommet voulez vous supprimer?\n Entrer son ID :\t";
        cin>> sommet;

        this->del_vertex(sommet);

    }
    if(m_interface->m_but_deledge.clicked())
    {
        int arete;
        cout<< " Quelle arete voulez vous supprimer?\n Entrer son ID :\t";
        cin>> arete;

        this->del_edge(arete);

    }

    // LES ADDS
//        void add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name="", int pic_idx=0 );
//        void add_interfaced_edge(int idx, int vert1, int vert2, double weight=0);

        //vertex
    if(m_interface->m_but_addvert.clicked())
    {
        map<int, Vertex>::iterator it = m_vertices.end();
        int id = it->first +1;
        int value,x,y;
        int pic_idx=0;
        string pic_name;
        cout<< " Quel est la valeur de ce sommet ?\n Entrer son poids entre 0 et 100 :\t";
        cin>> value;cout<<endl;
        cout<< " Quel les positions de ce sommet ?\n Entrer sa coordonnées X comprises entre 0 et 753:\t";
        cin>> x;cout<<endl;
        cout<< " Entrer sa coordonnées y comprises entre 0 et 615:\t";
        cin>> y;cout<<endl;
        cout<< " Quel est le nom (et extension) de l'image à charger dans le fichier pics ?\t";
        cin>> pic_name;cout<<endl;
        cout<< " L'image a-t-elle un id particulier? ?\n Si non, entrer 0:\t";
        cin>> pic_idx;cout<<endl;

        add_interfaced_vertex(id, value, x,y,pic_name, pic_idx);

    }

        //edge
    if(m_interface->m_but_addedge.clicked())
    {
        map<int, Edge>::iterator it = m_edges.end();
        int id = it->first +1;
        int sommet1,sommet2;
        double weight;
        cout<< " De quel sommet cette arete part-elle?\n Entrer son ID :\t";
        cin>> sommet1;cout<<endl;
        cout<< " Vers quel sommet cette arete va-t-elle?\n Entrer son ID :\t";
        cin>> sommet2;cout<<endl;
        cout<< " Quel est le poids de cette arete ?\n Entrer son poids entre 0 et 100 :\t";
        cin>> weight;cout<<endl ;

        add_interfaced_edge(id,sommet1, sommet2, weight);

    }

    // Les algos
    if(m_interface->m_but_kosaraju.clicked())
    {
        int sommet;
        cout<< " Quel sommet voulez vous supprimer?\n Entrer son ID :\t";
        cin>> sommet;

        this->del_vertex(sommet);

    }
    if(m_interface->m_but_konnexite.clicked())
    {
        int sommet;
        cout<< " Quel sommet voulez vous supprimer?\n Entrer son ID :\t";
        cin>> sommet;

        this->del_vertex(sommet);

    }
}





void Graph::show_vertex_edges(int id)
{
      std::cout <<std::endl<< " Sommet "<< id;
    std::cout <<std::endl<< "       les arcs entrants sont : "<<endl;
        for(vector<int>::iterator i = m_vertices[id].m_ein.begin() ; i != m_vertices[id].m_ein.end() ; ++i )
        {
            cout<< "\t\t" << *i << "  " << m_edges[*i].m_from << "->" << m_edges[*i].m_to << " " << m_edges[*i].m_weight << std::endl;
        }
        cout<<std::endl;

        std::cout <<std::endl<< "       les arcs sortants sont : "<<endl;
        for(vector<int>::iterator i = m_vertices[id].m_eout.begin() ; i != m_vertices[id].m_eout.end() ; ++i )
        {
            cout<< "\t\t" << *i << "  " << m_edges[*i].m_from << "->" << m_edges[*i].m_to << " " << m_edges[*i].m_weight << std::endl;
        }
        cout<< std::endl<<std::endl;

}

void Graph::fill_edge_list(vector<int>& edge_list_removal,int v_id)
{

    edge_list_removal.clear(); // sinon il va avoir les anciens numéros d'aretes
    if( !m_vertices[v_id].m_eout.empty() )
    {
     for(vector<int>::iterator i = m_vertices[v_id].m_eout.begin() ; i != m_vertices[v_id].m_eout.end() ; ++i )
        {            edge_list_removal.push_back(*i);        }
    }
    if( !m_vertices[v_id].m_ein.empty() )
    {
        for(vector<int>::iterator i = m_vertices[v_id].m_ein.begin() ; i != m_vertices[v_id].m_ein.end() ; ++i )
        {            edge_list_removal.push_back(*i);        }
    }
}

void Graph:: DFS(std::stack <int> &DFS_S, std::stack <int> &V_o_p, int &S_d_d)
{
    int interm_var(-1);//pour recuperer le numero de sommet qu'on va ajouter (ou pas) dans les piles
    bool neighboor_check(true);//variable pour verifier si on a les voisins non-visitees

    while(S_d_d<0)//tant que on n'as pas de sommet e depart pour notre dfs
    {
       for(auto &it: m_vertices)//le premier sommet non marque qu'on trouve devient notre sommet de depart
       {
           if(it.second.marker==false)
           {
              S_d_d=it.first;
           }
       }
       DFS_S.push(S_d_d);
       m_vertices[DFS_S.top()].marker=true;
    }
    neighboor_check=false;
    for(auto &it :m_vertices[DFS_S.top()].m_out)//on cherche les voisins non marquees
    {

        if(m_vertices[it].marker==false)//si on en trouve on le prends pour ajouter dans la pile (du coup ca sera le dernier voisin non marque de la liste qui sera ajoute)
        {
           interm_var=it;
           neighboor_check=true;

        }
    }

    if(neighboor_check)//si on a trouve un voisin non marque on l'ajoute dans la pile de DFS et on le marque
    {
       DFS_S.push(interm_var);
       m_vertices[interm_var].marker=true;
    }
    else//si il n'y a pas de voisins non marquees
    {
       if(DFS_S.size()>1)//si pile contient + qu'un element
       {
          V_o_p.push(DFS_S.top());//on ajoute le sommet avec le temps de passage + eleve dans notre pile de kosaraju
          DFS_S.pop();//on supprime cette sommet de pile de DFS pour verifier les voisins de sommet precedent
       }
       else //pour eviter les problemes de memoire, quand dans la pile DFS il ne reste + qu'un sommet, on fait la meme chose qu'avant, et apres ca on indique qu'il faudra parcourir le graph pour trouver un nouvelle sommet de depart(si besoin)
       {
          V_o_p.push(DFS_S.top());
          DFS_S.pop();
          S_d_d=-1;
       }
    }
}
void Graph:: Inversed_DFS(std::stack <int> &DFS_S, std::stack <int> & V_o_p, int &color, int &S_d_d)
{
    int interm_var(-1);
    bool neighboor_check(true);
    ///si on n'as pas encore choisi le sommet de depart, on le choisit
    while(S_d_d==-1)
    {  ///LE principe de Kosaraju est suivant: on prends la sommet de top de pile (le sommet avec le temps de passage + eleve), et on y applique le DFS
       if(m_vertices[V_o_p.top()].marker==false)//des que dans notre
       {
         S_d_d=V_o_p.top();
         DFS_S.push(S_d_d);
         m_vertices[DFS_S.top()].marker=true;
         color++;
         m_vertices[DFS_S.top()].m_color=color;
       }
       else
       {
         V_o_p.pop();
       }
    }
    //vu qu'on doit faire le DFS pour le transposee de graphique, au lieu d'inverser toutes les
    neighboor_check=false;
    for(auto &it :m_vertices[DFS_S.top()].m_in)//si on a trouve le voisin non marque, on le prends pour ensuite ajouter au top de pile
    {
        if(m_vertices[it].marker==false)
        {
           interm_var=it;
           neighboor_check=true;
        }
    }

    if(neighboor_check)//on l'ajoute au top de pile et on le marque+ on lui affectue a un composant fortement connexe qu'on parcours en ce moment
    {
       DFS_S.push(interm_var);
       m_vertices[interm_var].marker=true;
       m_vertices[interm_var].m_color=color;
    }
    else//si il n'y a pas de voisins
    {
       if(DFS_S.size()>1)
       {
          DFS_S.pop();
       }
       else
       {  DFS_S.pop();
          S_d_d=-1;
       }
    }
}
void Graph:: Search_of_CFC_Kosaraju()
{
    int i;
    int color(0);//variable qui indiquera l'appartenance d'un sommet a un composant fortement connexe concrete
    int Sommet_de_depart=-1;//sommet de depart pour les DFS (-1 car on ne peut pas tomber sur un sommet ave cun numero negatif)
    std::stack<int> DFS_stack;//pile pour faire le DFS
    std::stack <int> Verticles_in_order_of_passage;//pile qui contiendra les sommets dans l'ordre de passage specifique(des qu'on a plus de voisins a visiter, sommet est ajoute dans cette pile)
    bool check;//variable pour verifier si on a marque toutes les sommets

    ///Avant 'appliquer l'algo on reset l'appartenance a un certain composant connexe de chaque sommet a 0 et le marquage des sommets a 0
     for(auto &it : m_vertices)
       {
          it.second.m_color=0;
          it.second.marker=false;
       }

    check=false;
    do
    {

       check=true;

       for(auto &it : m_vertices)//si on trouvera un sommet non marque boucle continue a tourner
       {
           if(it.second.marker==false)
           check=false;
       }
       if(!check)//si il y a les sommets non marquees on effectue notre DFS modifie
       this->DFS(DFS_stack, Verticles_in_order_of_passage, Sommet_de_depart);


    }while(check!=true);//tant qu'on n'a pas marque toutes les sommets



    ///on reset le marquage pour appliquer le DFS encore une fois en suivant l'algo de Kosaraju
    for(auto &it : m_vertices)
       {
          it.second.marker=false;
       }


    ///La meme chose qu'avant, mais ce fois ci on appliquera autre DFS pour le aretes inversees (transposee de graph), chaque itteration complet de DFS nous donnera un composant fortement connexe
    check=false;
    Sommet_de_depart=-1;
    do
    {
       check=true;

       for(auto &it : m_vertices)
       {
          if(it.second.marker==false)
             check=false;
       }
       if(!check)
       this->Inversed_DFS(DFS_stack, Verticles_in_order_of_passage, color, Sommet_de_depart);

    }while(check!=true);

    ///algorithme est termine, on resete le marquage des sommets a 0
    for(auto &it : m_vertices)
    {
        it.second.marker=false;
        std::cout<<it.first<<" "<<it.second.m_color<<std::endl;
    }

}
