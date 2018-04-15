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
    m_slider_value.set_range(0.0 , 1000.0); // Valeurs arbitraires, à adapter...
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


        m_tool_box.add_child(m_but_show);
        m_but_show.set_frame(3,280, 98,40);
        m_but_show.set_bg_color(BLEU);
        m_but_show.set_gravity_x(grman::GravityX::Center);
        m_but_show.add_child(m_txt_show);
        m_txt_show.set_message("SHOW IN/OUt");

        m_tool_box.add_child( m_check_dyna );
        m_check_dyna.set_frame(3,325,98,40);
        m_check_dyna.set_bg_color(ORANGE);
        m_check_dyna.set_gravity_x(grman::GravityX::Center);
        m_check_dyna.add_child(m_txt_dyna);
        m_txt_dyna.set_message("DYNAMIQUE");


}



/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
  /*  // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

//    /// Les sommets doivent être définis avant les arcs
//    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
//    add_interfaced_vertex(0, 30.0, 200, 100, "clown1.jpg");
//    add_interfaced_vertex(1, 60.0, 400, 100, "clown2.jpg");
//    add_interfaced_vertex(2,  50.0, 200, 300, "clown3.jpg");
//    add_interfaced_vertex(3,  0.0, 400, 300, "clown4.jpg");
//    add_interfaced_vertex(4,  100.0, 600, 300, "clown5.jpg");
//    add_interfaced_vertex(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg", 0);
//    add_interfaced_vertex(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
//    add_interfaced_vertex(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);
//
//    /// Les arcs doivent être définis entre des sommets qui existent !
//    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
//    add_interfaced_edge(0, 1, 2, 50.0);
//    add_interfaced_edge(1, 0, 1, 50.0);
//    add_interfaced_edge(2, 1, 3, 75.0);
//    add_interfaced_edge(3, 4, 1, 25.0);
//    add_interfaced_edge(4, 6, 3, 25.0);
//    add_interfaced_edge(5, 7, 3, 25.0);
//    add_interfaced_edge(6, 3, 4, 0.0);
//    add_interfaced_edge(7, 2, 0, 100.0);
//    add_interfaced_edge(8, 5, 2, 20.0);
//    add_interfaced_edge(9, 3, 7, 80.0);*/
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




    // Label de visualisation d'index du edge dans une boite
    m_edges[idx].m_interface->m_top_edge.add_child( m_edges[idx].m_interface->m_box_label_idx );
    m_edges[idx].m_interface->m_box_label_idx.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);
    m_edges[idx].m_interface->m_box_label_idx.set_dim(15,12);


    m_edges[idx].m_interface->m_box_label_idx.add_child( m_edges[idx].m_interface->m_label_idx );
    m_edges[idx].m_interface->m_label_idx.set_message( std::to_string(idx) );

//    // Le slider de réglage de valeur
//    m_edges[idx].m_interface->m_top_edge.add_child( m_edges[idx].m_interface->m_slider_weight );
//    m_edges[idx].m_interface->m_slider_weight.set_range(0.0,100.0);
//    m_edges[idx].m_interface->m_slider_weight.set_dim(16,40);
//    m_edges[idx].m_interface->m_slider_weight.set_gravity_y(grman::GravityY::Up);
//    m_edges[idx].m_interface->m_slider_weight.set_value( weight );



    // Label de visualisation de valeur



//    m_slider_weight.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
//    m_slider_weight.set_dim(16,40);
//
//    m_edges[idx].m_interface->m_top_edge.add_child( m_edges[idx].m_interface->m_label_weight );
//    m_edges[idx].m_interface->m_label_weight.set_message( std::to_string( weight ) );
//    m_edges[idx].m_interface->m_label_weight.set_gravity_y(grman::GravityY::Down);

    m_edges[idx].pre_update();



    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;
    m_vertices[id_vert1].m_eout.push_back(idx);
    m_vertices[id_vert2].m_ein.push_back(idx);
    m_vertices[id_vert1].m_out.push_back(id_vert2);
    m_vertices[id_vert2].m_in.push_back(id_vert1);

}
 /// REQUEST NAME FILE TO SAVE
void Graph::save_graph()
{
    std::string name_file;



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
    for ( auto& i : m_edges )//unsigned int i = 0; i< m_edges.size(); i++)
    {
        file_save<< i.first<<" "<< i.second.m_from << " "<< i.second.m_to << " "<< i.second.m_weight<<std::endl;
    }

    std::cout<< "Sauvegarde du graphe effectuée !" <<std::endl;
}

using namespace std;
/// load a graph by giving the name file
void Graph::load_graph(string name_file)
{
    fstream ld_file( name_file.c_str(), ios::in );

    /// Traitement
    if(!ld_file.is_open()){ cout << " ERROR: can't open the save file"<<endl; }
    else
    {
            m_vertices.clear();
        m_edges.clear();


        int ordre, nb_aretes;
        int vid, vx, vy,vpic_id,eid,es1,es2;
        double vvalue,ew;
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
            ld_file>>eid>> es1>>es2>>ew;

            add_interfaced_edge(eid,es1,es2,ew);
        }

    }

}

/// Basé sur le code fourni sur campus
/// Supprime l'arete et ses entrées d'id dans les maps et vertex

void Graph::del_edge(int eidx)
{
    Edge &remed=m_edges.at(eidx);


        std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;

    {
        {
                 /// référence vers le Edge à enlever

        std::cout <<  std::endl;


         /// test : on a bien des éléments interfacés

        if (m_interface && remed.m_interface)
        {
            m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
        }

        m_edges.erase( eidx );
        /// On supprime dans les sommets la présences de l'entrée et/ou sortie des ids edge

        for( map< int, Vertex>::iterator x = m_vertices.begin() ; x != m_vertices.end() ; ++x )
        {
            x->second.m_ein.erase( remove( x->second.m_ein.begin() , x->second.m_ein.end() , eidx ), x->second.m_ein.end() );
            x->second.m_eout.erase( remove( x->second.m_eout.begin() , x->second.m_eout.end() , eidx ), x->second.m_eout.end() );
        }

        /// POOUR DES QUESTIONS DE COMPATIBILITES
            /// on a aussi les sommets qui ont des vecteurs contenant l'id des sommets qui sont reliés à eux
            /// une fois l'arc supprimé, ont doit aussi effacer cette liaison
            /// c'est basiquement (simplement) la même chose qu'au dessus, et  même si on aurait pu accèder à ça grâce à l'intermédiaire
            /// de m_in[i].m_from , le travail en parallèle fait qu'il est bien plus simple d'écrire ces lignes de codes



          vector<int>::iterator it = find(m_vertices[ remed.m_from ].m_out.begin(), m_vertices[ remed.m_from ].m_out.end(),  remed.m_to  );
          if( it != m_vertices[ remed.m_from ].m_out.end() ) m_vertices[ remed.m_from ].m_out.erase(it);

          it = find(m_vertices[ remed.m_from ].m_in.begin(), m_vertices[ remed.m_from ].m_in.end(),  remed.m_to  );
          if( it != m_vertices[ remed.m_from ].m_in.end() ) m_vertices[ remed.m_from ].m_in.erase(it);

            it = find(m_vertices[ remed.m_to ].m_out.begin(),m_vertices[ remed.m_to ].m_out.end(), remed.m_from  );
          if( it != m_vertices[ remed.m_to ].m_out.end() ) m_vertices[ remed.m_to ].m_out.erase(it);
            it = find(m_vertices[ remed.m_to ].m_in.begin(),m_vertices[ remed.m_to ].m_in.end(), remed.m_from  );
          if( it != m_vertices[ remed.m_to ].m_in.end() ) m_vertices[ remed.m_to ].m_in.erase(it);






        /// FAit pour réorganiser la map et la runémérotant mais ça marche vraiment pas



        //std::cout<<std::endl<< " putain de size 3 "<< m_edges.size()<<endl;
        }//else{ std::cout<< " ERROR: EDGE ID SUPERIOR TO NUMBER OF EDGE IN THIS GRAPH, C4N'T DELETE "<<std::endl; }

    }
    //else{ std::cout<< " ERROR: EDGE ID SUPERIOR TO NUMBER OF EDGE IN THIS GRAPH, C4N'T DELETE "<<std::endl; }


}



/// Adapté du code fourni sur les edges
/// supprime d'abord les edges et ensuite le sommet et ses entrées
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

    int sizein = m_vertices[v_id].m_ein.size() ;
    int sizeout =m_vertices[v_id].m_eout.size() ;

    for(auto nb_in =0 ; nb_in < sizein ; nb_in++  )
    {
        vector<int>::iterator x = m_vertices[v_id].m_ein.begin();
        del_edge( *x );
    }
    for(auto nb_out =0 ; nb_out < sizeout ; nb_out++  )
    {
        vector<int>::iterator x = m_vertices[v_id].m_eout.begin();
        del_edge( *x );
    }


    Vertex &delver=m_vertices.at(v_id);
    /// si les interfaces sont communes
    if( m_interface && delver.m_interface ) m_interface->m_main_box.remove_child( delver.m_interface->m_top_box );
    /// on retire la parenté entre l'interface du vertex et du graphe



    m_vertices.erase( v_id ); // on enlève le sommet de la liste

            /// FAit pour réorganiser la map et la runémérotant mais ça marche vraiment pas

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
        int id = it->first;
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
        map<int, Edge>::iterator it = m_edges.find(  m_edges.size()+1 );

        while( it != m_edges.end() ){  m_edges.size()+1; }

        int id = it->first +1;
        int sommet1,sommet2;
        double weight;
        cout<< " De quel sommet cette arete part-elle?\n Entrer son ID :\t";
        cin>> sommet1;cout<<endl;
        cout<< " Vers quel sommet cette arete va-t-elle?\n Entrer son ID :\t";
        cin>> sommet2;cout<<endl;
        cout<< " Quel est le poids de cette arete ?\n Entrer son poids entre 0 et 100 :\t";
        cin>> weight;cout<<endl ;
        double *p;
        p = &weight;


        add_interfaced_edge(id,sommet1, sommet2, *p);

        cout<< " CREATED EDGE WITH ID: " << id <<endl;
        //this->update();
        grman::mettre_a_jour();
        grman::rafraichir_clavier_souris();
    }

    // Les algos
    if(m_interface->m_but_kosaraju.clicked())
    {

        cout<< " ALGORITHME DE KOSERAJU:\n";
        this->Search_of_CFC_Kosaraju();



    }
    if(m_interface->m_but_konnexite.clicked())
    {
        cout<< " K CONNEXITE:\n"<<endl;
        this->K_connex_search();
    }

    if(m_interface->m_but_show.clicked())
    {
        int sommet;
        cout<< " Quel sommet voulez vous voir les edges?\n Entrer son ID :\t";
        cin>> sommet;

        this->show_vertex_edges(sommet);
    }

    if(m_interface->m_check_dyna.get_value()  )
    {
       // dyna_graph();
    }


}


/// va rendre l'éco sys dynamique
void Graph::dyna_graph()
{
    map<int, double> new_values;
    double buffer;
    double k=0;
    double p=0;
    bool sustain= false;
    for( auto& x : m_vertices ) // on update tout sommet
    {
        for( auto& y : m_edges )
            {// on regarde si les coord d'une arete (from/to) = au sommet actuel
                if(y.second.m_to == x.first){k += y.second.m_weight * ( m_vertices[y.second.m_from].m_value ); sustain = true ;}
                if(y.second.m_from == x.first){ p+= y.second.m_weight*m_vertices[ y.second.m_to].m_value; }
            }
        if( sustain && k == 0 ){ k = x.second.m_value; }else{ if( !sustain && k==0 ){ k+=10; } }
    // on gere le cas oùle sommet n'a pas d'arete entrante
        buffer = x.second.m_value +  0.03*x.second.m_value*( 1 - x.second.m_value/(k*1) ) - 0.005*p;

        new_values[ x.first ] = buffer;
    }
    for(auto& x : new_values )
    {
        for( auto& y : m_vertices )
        {
            if( x.first == y.first ) y.second.m_value = x.second;
            if( x.second <0 ) x.second = 0;
        }
    }


    rest(500);

}
/// montre les edges d'un sommets
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
// unsused
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
/// Depth First Search 
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
/// Inversed Depth First Search 
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
///Kosaraju algorithm est inspire par cette video https://www.youtube.com/watch?v=5wFyZJ8yH9Q&t=324s
//sertt à trouvé les différentes composantes
void Graph:: Search_of_CFC_Kosaraju()
{
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
        switch(it.second.m_color )
        {
        case 0:
            it.second.m_interface->m_top_box.set_bg_color( NOIR ); break;
        case 1:
            it.second.m_interface->m_top_box.set_bg_color( FUCHSIA); break;
            case 2:
            it.second.m_interface->m_top_box.set_bg_color( ROSE); break;
            case 3:
            it.second.m_interface->m_top_box.set_bg_color( MARRON); break;
            case 4:
            it.second.m_interface->m_top_box.set_bg_color( ROSESOMBRE); break;
            case 5:
            it.second.m_interface->m_top_box.set_bg_color( ROSECLAIR); break;
            case 6:
            it.second.m_interface->m_top_box.set_bg_color( VERT); break;
            case 7:
            it.second.m_interface->m_top_box.set_bg_color( CYAN); break;
            case 8:
            it.second.m_interface->m_top_box.set_bg_color( GRIS); break;
            case 9:
            it.second.m_interface->m_top_box.set_bg_color( VIOLET); break;
            case 10:
            it.second.m_interface->m_top_box.set_bg_color( BLEU); break;
            case 11:
            it.second.m_interface->m_top_box.set_bg_color( VIOLETSOMBRE); break;
            case 12:
            it.second.m_interface->m_top_box.set_bg_color( SABLE); break;
            case 13:
            it.second.m_interface->m_top_box.set_bg_color( FUCHSIASOMBRE); break;
            case 14:
            it.second.m_interface->m_top_box.set_bg_color( ORANGECLAIR); break;
            case 15:
            it.second.m_interface->m_top_box.set_bg_color( MARRONCLAIR); break;
            case 16:
            it.second.m_interface->m_top_box.set_bg_color( SABLESOMBRE); break;
            case 17:
            it.second.m_interface->m_top_box.set_bg_color( FUCHSIACLAIR); break;
        }


    }

}
/// DFS pour vérifier la connexite grace à une recherche non orientée
void Graph:: Non_oriented_DFS(std::stack<int>&DFS_S)
 {
     int interm_var;
     bool neighboor_check;
     //Le DFS pour verifier la connexite commence 
     neighboor_check=false;
     for(auto &it :m_vertices[DFS_S.top()].m_out)//on cherche les voisins non marquees
     {

         if(m_vertices[it].marker==false && m_vertices[it].active==true)//si on en trouve on le prends pour ajouter dans la pile (du coup ca sera le dernier voisin non marque de la liste qui sera ajoute)
         {
            interm_var=it;
            neighboor_check=true;

         }
     }
     for(auto &it :m_vertices[DFS_S.top()].m_in)//on cherche les voisins non marquees
     {

         if(m_vertices[it].marker==false && m_vertices[it].active==true)//si on en trouve on le prends pour ajouter dans la pile (du coup ca sera le dernier voisin non marque de la liste qui sera ajoute)
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
     else
     {
       DFS_S.pop();
     }
 }

///Cette algorithme est le + performant que j;ai reussi a invente
//Pour cette algorithme il est sous ententu que le graph est connexe
//D'abord ca parcours le graph en supprimant les sommets 1 par 1, puis  chaque doublet possible, puischaque triplet possible etc
//a chaque suppression ca verifie si le graph est connexe pas, si il n'est plus connexe, il enregistre le degree de suppression (1 sommet, 2 ou 3 etc...)
//c'est le degree de connexite de notre graphe en sommet
//puis ensachant cette degtree ca va donc essayer de supprimer toutes les k(degree)-plets possibles a chaque fois verifiant si le graphe est connexe ou pas 
//si il ne'est plus connexe, le k-plet va etre ajoute dans le vecteur, qui contient les vecteurs de ces k-plets
//ans ce vectuer on aura toutes les k-plets qu'on peut supprimer pour rendre le graph non-connexe
//ah oui, j'ai oublie de dire, que pour verifier la connexite- c'est le DFS qui ne prends pas en compte l'orientation des arretes que j'uitlise

 void Graph:: K_connex_search()
 {
     int i;
     int Sommet_de_depart(-1);//pour le DFS
     int Current_k_degree(1);//degree current de connexite de graph(au debut il est a 1)
     int Final_k_Degree(-1);//degree qu'on determinera
     bool check (false);//pour faire les petites verifications par ci par la
     bool k_con_el_check(false);//pour la deuxhieme partie d'algo quand on cherche toutes les sommets posibles a supprimer
     bool K_conn_found (false);//pour la premiere partie d'algo quand on determine la k-connexite 
     std::stack <int> DFS_S;//pile basique de DFS
     std::stack <int> Verticles_in_order_of_passage;//pile dans laquelle on va stocker toutes les sommets qui n;ont pas encore ete teste a un certain degree de connexite
     std::vector <std::vector <int>> Breaking_graph_verticles_container;//vecteur qui contiendra les k-plets des sommmets qui vont rendre le graph non connexe 
     std::vector <int> Current_breaking_verticles;//vecteur qui contiendra le k-plet des sommets current quon a teste
     check=false;
     ///on netoi les valeurs, avant d'executer l'algo
     for(auto& it: m_vertices)
        {
           it.second.marker=false;
           it.second.active=true;
           it.second.tried=false;
        }




     K_conn_found=false;

     while(K_conn_found!=true)//tant qu'on ne trouve pas le degree de k-connexite
     {


         K_conn_found==false;





     //on verifie si on a essaye toutes les sommets a certain degree, si oui mais on n'as pas reussi a "deconnexifier" la graph on augment l'e degree 
         check=true;
         for(auto& it: m_vertices)
         {
             if (it.second.tried==false)
             {
                check=false;
             }
         }
         if(check==true && Final_k_Degree<0)
         {
            Current_k_degree++;
            for(auto& it: m_vertices)
            {
                it.second.tried=false;
            }
         }

         //on rempli le V_O_P si il est vide
         if (Verticles_in_order_of_passage.size()==0)
         {
             for(auto& it: m_vertices)
              {
                 if (it.second.tried!=true)//que avec les sommets qui on pas encore ete verifie
                 {
                   Verticles_in_order_of_passage.push(it.first);
                 }
              }
              for(i=0;i<Current_k_degree;i++)//le vecteur qui possiblement contiendra le k-plet
              {
                  Current_breaking_verticles.push_back(Verticles_in_order_of_passage.top());
                  m_vertices[Verticles_in_order_of_passage.top()].tried=true;
                  m_vertices[Verticles_in_order_of_passage.top()].active=false;
                  Verticles_in_order_of_passage.pop();
              }

         }


        //tant qu'on n'as pas vide notrte pile pour verifier les sommets pour la rupture de connexite 
         while (Verticles_in_order_of_passage.size()!=0)
         {

            if(Current_breaking_verticles.size()==Current_k_degree)
            {


               for(auto& it: m_vertices)//on cherche un sommet qu'on n'as pas encore verifie pour etre sommet de rupture, qui est active(on ne l'as pas virtuelement supprime de graphique) et qu'on n'as pas encore passe avec DFS
               {
                   if(it.second.marker==false && it.second.active==true)
                   Sommet_de_depart=it.first;

               }//on le met dans notre pile de DFS
               DFS_S.push(Sommet_de_depart);

               m_vertices[Sommet_de_depart].marker=true;//on marque ce sommet comme tant passe par le DFS

               while (DFS_S.size()!=0)//On commence le DFS et on le fait tant qu'on ne parcoutrs pas l'element connexe de graphe
               {
               this->Non_oriented_DFS(DFS_S);
               }

               //si le dfs a ete effectue mais on n'as pas trpuve les sommets non marquees, alors on n'a pas trouve l'ordre de k-connexite
               for(auto &it: m_vertices)
               {
                  if(it.second.marker==false && it.second.active==true)//si on trouve un sommet non marque par le DFS alors qu'il etait actif, on a l'ordre de connexité de notre graphe 
                  {
                     K_conn_found=true;
                     Final_k_Degree=Current_k_degree;
                  }
               }
                for(auto &it: m_vertices)//on remet le marquage de DFS a false
               {
               it.second.marker=false;
               }
               if(K_conn_found)//SI on a trouve l'ordre de connexite de graph on vide le pile de sommets pour sortir de boucle
               {
                  while(Verticles_in_order_of_passage.size()!=0)
                  {
                        Verticles_in_order_of_passage.pop();
                  }
               }
               else//si non on netoi le vecteur qui possiblement contiendra le k-plet pour le reremplir ensuite
               {
                m_vertices[Current_breaking_verticles[Current_breaking_verticles.size()-1]].active=true;
                Current_breaking_verticles.pop_back();
                Current_breaking_verticles.push_back(Verticles_in_order_of_passage.top());
                m_vertices[Verticles_in_order_of_passage.top()].active=false;
                if(Current_k_degree==1)
                {
                    m_vertices[Verticles_in_order_of_passage.top()].tried=true;
                }
                Verticles_in_order_of_passage.pop();

               }

            }

         }

     }




  for(auto& it: m_vertices)//On remet toutes les markeurs dans leur etat initial
  {
      it.second.marker=false;
      it.second.active=true;
      it.second.tried=false;
  }
 while (Current_breaking_verticles.size()!=0)//on netoit notre vecteur de k-plets
 {
        Current_breaking_verticles.pop_back();
 }


   k_con_el_check=false;//on commence a chercher toutes les k-plets pouvant couper la connexite de notre graphe a degree qu'on a eja trouve
   while (k_con_el_check!=true)
   {
       k_con_el_check=true;
       //on regarde si on a verifie toutes les sommets et si non on continue
       for(auto& it: m_vertices)
         {

             if (it.second.tried==false)
             {
                k_con_el_check=false;

             }
         }

         //on rempli notre pile de sommets a verifier si il est vide
        if(k_con_el_check==false)
        if (Verticles_in_order_of_passage.size()==0)
         {

             for(auto& it: m_vertices)
              {

                 if (it.second.tried!=true)
                 {
                   Verticles_in_order_of_passage.push(it.first);
                 }
              }
              for(i=0;i<Final_k_Degree;i++)//on rempli notre vecteur de k-plets 
              {

                  Current_breaking_verticles.push_back(Verticles_in_order_of_passage.top());
                  m_vertices[Verticles_in_order_of_passage.top()].tried=true;
                  m_vertices[Verticles_in_order_of_passage.top()].active=false;

                  Verticles_in_order_of_passage.pop();
              }


         }
         //tant que notre pile de sommets a verifier n'est pas vide on effectue la meme procudure que avant sauf quelaue changement
         while (Verticles_in_order_of_passage.size()>1)
         {
            if(Current_breaking_verticles.size()==Final_k_Degree)
            {
               for(auto& it: m_vertices)
               {
                   if(it.second.marker==false && it.second.active==true)
                   Sommet_de_depart=it.first;


               }

               DFS_S.push(Sommet_de_depart);

               m_vertices[Sommet_de_depart].marker=true;

               while (DFS_S.size()!=0)
               {
                     this->Non_oriented_DFS(DFS_S);
               }

               //si on a reussi a trouver un sommet non marque par le DFS alors qu'il est actif, on ajoute notre vecteur de k-plet ans le vecteur de toutes les k-pleut coupant la connexite de graph
               check=false;
               for(auto &it: m_vertices)
               {
                  if(it.second.marker==false && it.second.active==true)
                  {
                    check=true;
                  }
               }
               if(check)
               {
                  Breaking_graph_verticles_container.push_back(Current_breaking_verticles);
               }
               for(auto &it: m_vertices)
               {
                  it.second.marker=false;
               }
            //on netoit notre vecteur de k-plets
            m_vertices[Current_breaking_verticles[Current_breaking_verticles.size()-1]].active=true;
            Current_breaking_verticles.pop_back();
            Current_breaking_verticles.push_back(Verticles_in_order_of_passage.top());
            m_vertices[Verticles_in_order_of_passage.top()].active=false;
            if(Current_k_degree==1)
            {
                m_vertices[Verticles_in_order_of_passage.top()].tried=true;
            }
            Verticles_in_order_of_passage.pop();

            }



         }

         if(Verticles_in_order_of_passage.size()==1)
         {

            m_vertices[Current_breaking_verticles[Current_breaking_verticles.size()-1]].active=true;
            Current_breaking_verticles.pop_back();
            Current_breaking_verticles.push_back(Verticles_in_order_of_passage.top());
            m_vertices[Verticles_in_order_of_passage.top()].active=false;
            if(Current_k_degree==1)
            {
                m_vertices[Verticles_in_order_of_passage.top()].tried=true;
            }
            Verticles_in_order_of_passage.pop();
         }




   }
///on affcihe les resultats
std::cout<<"This Graph is of "<< Final_k_Degree<<" - connectivity"<<std::endl;
std::cout<<"Vertex groups that we have to delete are: "<<std::endl;



for (auto &it : Breaking_graph_verticles_container)
{
std::cout<<"Group: "<<std::endl;
for (auto & et : it )
{
std:: cout<<et<<std::endl;
}
}

 for(auto& it: m_vertices)
  {
      it.second.marker=false;
      it.second.active=true;
      it.second.tried=false;
  }

 }


