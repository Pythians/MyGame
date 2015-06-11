﻿#include "Lightning.h"

using std::vector;

Lightning::Lightning( )
	: m_ForceTexLoop( false )
	, m_Time( 0.0 )
	, m_Width( 1.0 )
	, m_Step( 2.0 )
	, m_TextureLength( 2.0 )
	, m_Amplitude0( 2.0 )
	, m_Amplitude1( 2.0 )
	, m_Frequency0( 2 )
	, m_Frequency1( 100 )
	, m_VertexVector( NULL )
	, m_ProgramState( NULL )
	, m_RenderMesh( NULL )
	, m_TimeFactor( 1.0 )
	, m_Attenuation( 0.0 )
	, m_fTotalAlphaToZeroTime( -1.0 )
	, m_fLeaveAlphaToZeroTime( -1.0 )
	//, m_LineType( LT_PerlinNosie )
	, m_Color( Vec4::ZERO )
	, m_Dirty( true )
	, m_ForceUpdate( false )
	, m_pMeshCommand( NULL )
{
	gettimeofday( &m_LastTime, nullptr );
	m_Lines.clear( );

}

Lightning::~Lightning( )
{
	CC_SAFE_DELETE( m_pMeshCommand );
}

bool Lightning::init( )
{
	m_VertexVector = new VertexVector( true, 512 );
	m_VertexVector->init( );

	m_Texture = _director->getTextureCache( )->addImage( "lighting.png" );
	m_BlendFunc = BlendFunc::ADDITIVE;

	// 装配完整 Shader 文件
	auto glprogram = GLProgram::createWithFilenames( "LightLineRender.vsh", "LightLineRender.fsh" );
	m_ProgramState = GLProgramState::getOrCreateWithGLProgram( glprogram );
	this->setGLProgramState( m_ProgramState );
	m_ProgramState->setUniformTexture( "u_texture", m_Texture );

	return true;
}

void Lightning::draw(  Renderer * renderer, const Mat4 & transform, uint32_t flags )
{
	
	if( m_VertexVector )
	{
		timeval currtime;
		gettimeofday( &currtime, nullptr );
		float dt = ( currtime.tv_sec - m_LastTime.tv_sec ) + ( currtime.tv_usec - m_LastTime.tv_usec ) / 1000000.0f;
		m_Time += dt;
		m_LastTime = currtime;
		if( m_ForceUpdate || m_Dirty )
		{
			m_VertexVector->clear( );
			updateMesh( );
		}
		if( m_Texture )
		{
			ccGLBindTexture2D( m_Texture->getName( ) );
			ccGLBlendFunc( m_BlendFunc.src, m_BlendFunc.dst );
		}
		GLProgramState * programstate = getGLProgramState( );
		Color4F color( getDisplayedColor( ) );
		color.a = getDisplayedOpacity( ) / 255.0f;

		CC_SAFE_DELETE( m_pMeshCommand );
		GLuint textureID = m_Texture->getName( );
		m_pMeshCommand = new MeshCommand( );
		//m_pMeshCommand->genMaterialID( textureID, m_ProgramState, 0,  );
		m_pMeshCommand->init( _globalZOrder,
							  textureID,
							  programstate,
							  m_BlendFunc,
							  m_RenderMesh->getVertexBuffer( ),
							  m_RenderMesh->getIndexBuffer( ),
							  ( GLenum ) m_RenderMesh->getPrimitiveType( ),
							  ( GLenum ) m_RenderMesh->getIndexFormat( ),
							  m_RenderMesh->getIndexCount( ),
							  transform );
		m_pMeshCommand->setCullFaceEnabled( false );
		m_pMeshCommand->setDepthTestEnabled( false );

		if( m_fLeaveAlphaToZeroTime >= 0 )
		{
			m_fLeaveAlphaToZeroTime -= dt;
			if( m_fLeaveAlphaToZeroTime < 0 )
			{
				m_fLeaveAlphaToZeroTime = 0;
			}
			m_pMeshCommand->setDisplayColor( Vec4( color.r, color.g, color.b, m_fLeaveAlphaToZeroTime / m_fTotalAlphaToZeroTime ) );
		}
		else
		{
			m_pMeshCommand->setDisplayColor( Vec4( color.r, color.g, color.b, color.a ) );
		}
		_director->getRenderer( )->addCommand( m_pMeshCommand );
	}

	Node::draw( renderer, transform, flags );
}

void Lightning::updateMesh( void )
{
	// 每段线，每个三角形
	for( unsigned int i = 0; i < m_Lines.size( ); ++i )
	{
		float halfWidth = m_Width*0.5;
		float inverseTextueLength = ( m_TextureLength != 0 )?( 1 / m_TextureLength ):1.0;

		Vec3 lineBegin( m_Lines[ i ].lineBegin );
		Vec3 lineEnd( m_Lines[ i ].lineEnd );
		float beginOffset( m_Lines[ i ].beginOffset );
		Vec3 dir = lineEnd - lineBegin;
		float totalLength = dir.length( );
		dir.normalize( );
		float invTotalLength = ( totalLength != 0 )?( 1 / totalLength ):1.0;

		float step( m_Step );
		float stepCount = ( totalLength <= m_Step * 2 )?2:ceil( totalLength / step );
		step = totalLength / stepCount;

		// 计算展开朝向，展开朝向应该总是尽量向着相机
		Vec3 widthOffset;

		Vec3 camForward = Vec3( 0, 0, 1 );
		camForward.normalize( );

		widthOffset = dir;
		widthOffset.cross( camForward );
		widthOffset.normalize( );


		Vec3 stepBegin( lineBegin );
		Vec3 stepEnd( lineEnd );

		float curLength( 0.0 );

		for( int j = 0; j < stepCount - 1; ++j )
		{
			Vec3 randomPos;

			/*switch( m_LineType )
			{
				case LT_Direct:
				{
				}break;
				case  LT_Random:
				{
					randomPos = Vec3( m_Amplitude0, m_Amplitude0, m_Amplitude0 );
					randomPos.x *= RandomFloat( );
					randomPos.y *= RandomFloat( );
					randomPos.z *= RandomFloat( );
				}break;
				case  LT_PerlinNosie:
				{
					float noiseParam = ( m_Time*m_TimeFactor + curLength*invTotalLength + beginOffset );
					float noise = m_PerlinNoise.generateNoise1D( noiseParam*m_Frequency0 )*m_Amplitude0;
					noise += m_PerlinNoise.generateNoise1D( noiseParam*m_Frequency1 )*m_Amplitude1;

					float attenuationDis = C3D_Min( curLength, totalLength - curLength );

					if( attenuationDis < m_Attenuation )
					{
						noise *= pow( ( attenuationDis / m_Attenuation ), 4 );
					}

					randomPos = widthOffset*noise;
				}break;
			}*/

			stepEnd = lineBegin + dir*( curLength + step ) + randomPos;

			addOneStep( m_VertexVector, ( curLength == 0 )?lineBegin:stepBegin, stepEnd,
						widthOffset*halfWidth,
						curLength*inverseTextueLength - m_Time, ( curLength + step ) * inverseTextueLength - m_Time,
						( curLength == 0 )?ST_Begin:ST_Other, m_Color );

			//lastLength = curLength;
			curLength += step;
			stepBegin = stepEnd;
		}

		//尾
		float uvBegin( curLength*inverseTextueLength );
		float uvEnd( totalLength*inverseTextueLength );

		if( m_ForceTexLoop )
		{
			uvEnd = ceil( uvEnd );
		}
		addOneStep( m_VertexVector, stepBegin, lineEnd,
					widthOffset*halfWidth,
					uvBegin - m_Time, uvEnd - m_Time, ST_End, m_Color );
	}

	CC_SAFE_RELEASE_NULL( m_RenderMesh );

	unsigned char*	tpVertices = m_VertexVector->getVertices( );
	unsigned int	iVerticesCount = m_VertexVector->getVerticesCount( );
	unsigned short* tpIndices = m_VertexVector->getIndices( );
	unsigned int	iIndexCount = m_VertexVector->getIndexCount( );

	vector<float>	positions;
	vector<float>   normals;
	vector<float>   colors;
	vector<float>   texs;
	VertexColorCoord1*	pVertex = ( VertexColorCoord1* ) tpVertices;
	for( int v = 0; v < iVerticesCount; v++ )
	{
		positions.push_back( pVertex->position.x );
		positions.push_back( pVertex->position.y );
		positions.push_back( pVertex->position.z );

		colors.push_back( pVertex->color.x );
		colors.push_back( pVertex->color.y );
		colors.push_back( pVertex->color.z );
		colors.push_back( pVertex->color.w );

		texs.push_back( pVertex->u );
		texs.push_back( pVertex->v );

		pVertex++;
	}

	std::vector<unsigned short> tTriangle;
	for( int i = 0; i < iIndexCount / 3; i++ )
	{
		tTriangle.push_back( tpIndices[ i * 3 ] );
		tTriangle.push_back( tpIndices[ i * 3 + 1 ] );
		tTriangle.push_back( tpIndices[ i * 3 + 2 ] );
	}

	m_RenderMesh = Mesh::create( positions, normals, texs, tTriangle );
	m_RenderMesh->retain( );


	long offset = 0;
	auto attributeCount = m_RenderMesh->getMeshVertexAttribCount( );
	for( auto k = 0; k < attributeCount; k++ )
	{
		auto meshattribute = m_RenderMesh->getMeshVertexAttribute( k );
		m_ProgramState->setVertexAttribPointer( s_attributeNames[ meshattribute.vertexAttrib ],
												meshattribute.size,
												meshattribute.type,
												GL_FALSE,
												m_RenderMesh->getVertexSizeInBytes( ),
												( GLvoid* ) offset );
		offset += meshattribute.attribSizeBytes;
	}

	m_Dirty = false;
}

void Lightning::addOneStep( VertexVector * mesh, Vec3 lineBegin, Vec3 lineEnd, Vec3 widthOffset, float uvBegin, float uvEnd, StepType stepType, Vec4 color )
{
	static const int VertexCount = 4;
	static const int IndexCount = 6;
	static unsigned short index[ IndexCount ] = { 0, 1, 2, 0, 2, 3, };
		

	static VertexColorCoord1 vertex[ VertexCount ];

	switch( stepType )
	{
		case ST_Begin:
		{
			vertex[ 0 ].position = lineBegin;
			vertex[ 1 ].position = lineEnd + widthOffset;
			vertex[ 2 ].position = lineEnd - widthOffset;
			vertex[ 3 ].position = lineBegin;

			vertex[ 0 ].u = uvBegin;
			vertex[ 1 ].u = uvEnd;
			vertex[ 2 ].u = uvEnd;
			vertex[ 3 ].u = uvBegin;

			vertex[ 0 ].v = 0.5;
			vertex[ 1 ].v = 0;
			vertex[ 2 ].v = 1;
			vertex[ 3 ].v = 0.5;

			vertex[ 0 ].color = color;
			vertex[ 1 ].color = color;
			vertex[ 2 ].color = color;
			vertex[ 3 ].color = color;
		}break;
		case  ST_End:
		{
			vertex[ 0 ].position = lineBegin + widthOffset;
			vertex[ 1 ].position = lineEnd;
			vertex[ 2 ].position = lineEnd;
			vertex[ 3 ].position = lineBegin - widthOffset;

			vertex[ 0 ].u = uvBegin;
			vertex[ 1 ].u = uvEnd;
			vertex[ 2 ].u = uvEnd;
			vertex[ 3 ].u = uvBegin;

			vertex[ 0 ].v = 0;
			vertex[ 1 ].v = 0.5;
			vertex[ 2 ].v = 0.5;
			vertex[ 3 ].v = 1;

			vertex[ 0 ].color = color;
			vertex[ 1 ].color = color;
			vertex[ 2 ].color = color;
			vertex[ 3 ].color = color;
		}break;
		case  ST_Other:
		{
			vertex[ 0 ].position = lineBegin + widthOffset;
			vertex[ 1 ].position = lineEnd + widthOffset;
			vertex[ 2 ].position = lineEnd - widthOffset;
			vertex[ 3 ].position = lineBegin - widthOffset;

			vertex[ 0 ].u = uvBegin;
			vertex[ 1 ].u = uvEnd;
			vertex[ 2 ].u = uvEnd;
			vertex[ 3 ].u = uvBegin;

			vertex[ 0 ].v = 0;
			vertex[ 1 ].v = 0;
			vertex[ 2 ].v = 1;
			vertex[ 3 ].v = 1;

			vertex[ 0 ].color = color;
			vertex[ 1 ].color = color;
			vertex[ 2 ].color = color;
			vertex[ 3 ].color = color;
		}break;
	}

	m_VertexVector->add( ( unsigned char* ) vertex, VertexCount, index, IndexCount );

}

Vec3 Lightning::getCenter( )
{
	Vec3 center;
	if( !m_Lines.empty( ) )
	{
		for( unsigned int i = 0; i < m_Lines.size( ); i++ )
		{
			center += m_Lines[ i ].lineBegin;
			center += m_Lines[ i ].lineEnd;
		}
		center.scale( 0.5 / m_Lines.size( ) );
	}
	return center;
}

void Lightning::setLines( const std::vector<Line>& lines )
{
	if( !m_Lines.empty( ) )
	{
		m_Lines.clear( );
		m_Lines.reserve( lines.size( ) );
	}

	m_Lines.insert( m_Lines.begin( ), lines.begin( ), lines.end( ) );

	Vec3 center = getCenter( );
	setPosition3D( center );

	m_Dirty = true;
}
