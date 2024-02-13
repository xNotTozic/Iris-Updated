#pragma once

enum IrisRenderType
{
    Multi,
    OneCall // our new renderer (epic !)
};

enum IrisRenderFace // for mesh faces
{
    Left, Right
};

// make 3d methods here cuz its easier to control
class ThreeUtil
{
public:
    static inline Vector3<int> cubeVertices[8] = { // cube vertices
        { 0, 0, 0 },
        { 0, 0, 1 },
        { 0, 1, 0 },
        { 0, 1, 1 },
        { 1, 0, 0 },
        { 1, 0, 1 },
        { 1, 1, 0 },
        { 1, 1, 1 }
    };

    static int oneCallsRendered;
    static int multisRendered;

    static void DrawLine(Vector3<float> p1, Vector3<float> p2, float thickness = 1, bool depthTesting = false)
    {
        Vector2<float> sp1, sp2;

        if (!Game::GetInstance()->WorldToScreen(p1, sp1) ||
            p1.x < 0 || p1.x > GuiInfo::ScreenRes.x || p1.y < 0 || p1.y > GuiInfo::ScreenRes.y) {
            return;
        }

        if (!Game::GetInstance()->WorldToScreen(p2, sp2) ||
            p2.x < 0 || p2.x > GuiInfo::ScreenRes.x || p2.y < 0 || p2.y > GuiInfo::ScreenRes.y) {
            return;
        }

        RenderUtil::drawLine(sp1.ToInt(), sp2.ToInt(), thickness);
    }

    static void DrawCube(Vector3<float> blockPos, UIColor colour, float thickness = 1, float lerpSpeed = 8, Vector3<float> verticesScale = {1, 1, 1}, IrisRenderType type = IrisRenderType::Multi)
    {
        Player* player = Game::GetLocalPlayer();
        if (!player || !Game::GetInstance())
            return;

        switch (type)
        {
        case Multi:
        {
        Vector2<float> screenPos[8];
        for (int i = 0; i < 8; i++)
        {
            Vector3<float> vertice = cubeVertices[i].ToFloat();

            if (vertice.x == 1)
                vertice.x = verticesScale.x;

            if (vertice.y == 1)
                vertice.y = verticesScale.y;

            if (vertice.z == 1)
                vertice.z = verticesScale.z;

            Vector3<float> vertexPos = blockPos + vertice;
            if (!Game::GetInstance()->WorldToScreen(vertexPos, screenPos[i]) || screenPos[i].x < 0 || screenPos[i].x > GuiInfo::ScreenRes.x || screenPos[i].y < 0 || screenPos[i].y > GuiInfo::ScreenRes.y) {
                return;
            }
        }

        RenderUtil::setColor(colour.r, colour.g, colour.b, colour.a);

        RenderUtil::drawLine(screenPos[0].ToInt(), screenPos[1].ToInt(), thickness);
        RenderUtil::drawLine(screenPos[0].ToInt(), screenPos[2].ToInt(), thickness);
        RenderUtil::drawLine(screenPos[0].ToInt(), screenPos[4].ToInt(), thickness);

        RenderUtil::drawLine(screenPos[1].ToInt(), screenPos[3].ToInt(), thickness);
        RenderUtil::drawLine(screenPos[1].ToInt(), screenPos[5].ToInt(), thickness);

        RenderUtil::drawLine(screenPos[2].ToInt(), screenPos[3].ToInt(), thickness);
        RenderUtil::drawLine(screenPos[2].ToInt(), screenPos[6].ToInt(), thickness);

        RenderUtil::drawLine(screenPos[3].ToInt(), screenPos[7].ToInt(), thickness);

        RenderUtil::drawLine(screenPos[4].ToInt(), screenPos[5].ToInt(), thickness);
        RenderUtil::drawLine(screenPos[4].ToInt(), screenPos[6].ToInt(), thickness);

        RenderUtil::drawLine(screenPos[5].ToInt(), screenPos[7].ToInt(), thickness);

        RenderUtil::drawLine(screenPos[6].ToInt(), screenPos[7].ToInt(), thickness);

        RenderUtil::flushImage();
        multisRendered++;
        }
            break;
        case OneCall:
        {
            Vector2<float> screenPos[8];
            Vector3<float> scaledVertices[8];

            for (int i = 0; i < 8; i++) {
                Vector3<float> vertice = cubeVertices[i].ToFloat();
                scaledVertices[i] = Vector3<float>(vertice.x * verticesScale.x, vertice.y * verticesScale.y, vertice.z * verticesScale.z);
                Vector3<float> vertexPos = blockPos + scaledVertices[i];
                if (!Game::GetInstance()->WorldToScreen(vertexPos, screenPos[i]) || screenPos[i].x < 0 || screenPos[i].x > GuiInfo::ScreenRes.x || screenPos[i].y < 0 || screenPos[i].y > GuiInfo::ScreenRes.y) {
                    return;
                }
            }

            RenderUtil::setColor(colour.r, colour.g, colour.b, colour.a);

            RenderUtil::tess->begin(VertextFormat::TRIANGLE_STRIP);

            int lines[12][2] = {
                {0, 4}, {5, 1}, {3, 7}, {6, 2},    // Connections between faces
                {4, 5}, {5, 7}, {7, 6}, {6, 4},   // Back face
                {0, 1}, {1, 3}, {3, 2}, {2, 0},   // Front face
            };

            for (int i = 0; i < 12; i++) {
                int start = lines[i][0];
                int end = lines[i][1];

                Vector2<int> startScreenPos = screenPos[start].ToInt();
                Vector2<int> endScreenPos = screenPos[end].ToInt();

                RenderUtil::tessLine(startScreenPos, endScreenPos, thickness);
            }

            RenderUtil::tess->renderMeshImmediately(RenderUtil::renderContext->ScreenContext, RenderUtil::uiMaterial);
            oneCallsRendered++;
        }
            break;
        }
    }

    static void DrawMeshFace(Vector3<float> blockPos, UIColor colour, float thickness = 1, Vector2<float> verticesScale = { 1, 1 }, IrisRenderFace face = IrisRenderFace::Left)
    {
        Player* player = Game::GetLocalPlayer();
        if (!player || !Game::GetInstance())
            return;

        Vector2<float> screenPos[8];
        Vector3<float> scaledVertices[8];

        //bool onScreen = false;

        for (int i = 0; i < 8; i++) {
            Vector3<float> vertice = cubeVertices[i].ToFloat();
            scaledVertices[i] = Vector3<float>(vertice.x, vertice.y * verticesScale.y, vertice.z * verticesScale.x);
            Vector3<float> vertexPos = blockPos + scaledVertices[i];
            if (!Game::GetInstance()->WorldToScreen(vertexPos, screenPos[i]) || screenPos[i].x < 0 || screenPos[i].x > GuiInfo::ScreenRes.x || screenPos[i].y < 0 || screenPos[i].y > GuiInfo::ScreenRes.y) {
                //onScreen = true;
                return;
            }
        }

        /*if (!onScreen)
            return;*/

        RenderUtil::setColor(colour.r, colour.g, colour.b, colour.a);

        RenderUtil::tess->begin(VertextFormat::TRIANGLE_STRIP);

        std::vector<std::vector<int>> lines;

        /*
        
                {0, 4}, {5, 1}, {3, 7}, {6, 2},   // Connections between faces
                {4, 5}, {5, 7}, {7, 6}, {6, 4},   // Back face
                {0, 1}, {1, 3}, {3, 2}, {2, 0},   // Front face

        */

        switch (face)
        {
        case IrisRenderFace::Left:
            lines = { {0, 1}, { 1, 3 }, { 3, 2 }, { 2, 0 } };
            break;
        case IrisRenderFace::Right:
            lines = { {0, 4}, {6, 4}, {6, 2}, { 2, 0 } };
            break;
        /*case IrisRenderFace::Up:
            lines = { {0, 1}, { 1, 3 }, { 3, 2 }, { 2, 0 } };
            break;*/
        }

        for (int i = 0; i < 4; i++) {
            int start = lines[i][0];
            int end = lines[i][1];

            Vector2<int> startScreenPos = screenPos[start].ToInt();
            Vector2<int> endScreenPos = screenPos[end].ToInt();

            RenderUtil::tessLine(startScreenPos, endScreenPos, thickness);
        }

        RenderUtil::tess->renderMeshImmediately(RenderUtil::renderContext->ScreenContext, RenderUtil::uiMaterial);
        oneCallsRendered++;
    }
};

int ThreeUtil::oneCallsRendered = 0;
int ThreeUtil::multisRendered = 0;