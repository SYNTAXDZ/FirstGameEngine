#include "LayerStack.hpp"

namespace FGE {

    LayerStack::~LayerStack() {

        for( Layer* layer : m_Layers ) {
            
            layer->OnDetach();
            delete layer;

        }

    }

    // PushLayer: Add a Layer After the Begin of Layers + The LayerInsertIndex
    // which Specify The Position of The Layer
    void LayerStack::PushLayer( Layer* layer ) {

        m_Layers.emplace( m_Layers.begin() + m_LayerInsertIndex, layer );
        m_LayerInsertIndex++;        

    }

    //PushOverlay: Add an overlay to The end of Layers
    void LayerStack::PushOverlay( Layer* layer ) {

        m_Layers.emplace_back( layer );

    }

    void LayerStack::PopLayer( Layer* layer ) {

        auto it = std::find( m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer );

        if( it != m_Layers.begin() + m_LayerInsertIndex ) {

            layer->OnDetach();
            m_Layers.erase( it );
            m_LayerInsertIndex--;

        }

    }

    void LayerStack::PopOverlay( Layer* layer ) {

        auto it = std::find( m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), layer );

        if( it != m_Layers.end() ) {

            layer->OnDetach();
			m_Layers.erase( it );

        }

    }

}