#pragma once

class ParticleUtil
{
public:
    struct Particle
    {
        float x, y; // position
        float vx, vy; // velocity
        float lifetime; // remaining lifetime of the particle
        float opacity; // opacity of the particle
        UIColor color; // color of the particle
        float size; // size of the particle
        float distance; // distance for particle to travel

        Particle() : x(0), y(0), vx(0), vy(0), lifetime(0), opacity(0), color(UIColor()), size(0), distance(0) {}
        Particle(float x, float y, float vx, float vy, float lifetime, float opacity, UIColor color, float size, float distance)
            : x(x), y(y), vx(vx), vy(vy), lifetime(lifetime), opacity(opacity), color(color), size(size), distance(distance) {}
    };

    // Store all the particles
    std::vector<Particle> particles;

    void addParticles(int numParticles, float startX, float startY, float distance, float size, float seconds = 4.f) 
    {
        for (int i = 0; i < numParticles; i++) 
        {
            Particle p;
            p.x = startX + rand() % 10 - 5;
            p.y = startY + rand() % 10 - 5;
            p.vx = rand() % 200 - 100 + rand() % 10 - 5;
            p.vy = rand() % 200 - 100 + rand() % 10 - 5;
            p.lifetime = seconds;
            p.opacity = 1.0f;
            p.color = ColorUtil::getClientColor(5, 1, 1, p.x * 45);
            p.size = size + rand() % ((int)size / 2 + 1);
            p.distance = distance;
            particles.push_back(p);
        }
    }

    void clearParticles()
    {
        particles.clear();
    }

    void updateParticles(float delta)
    {
        for (auto& p : particles) {
            EasingUtil easing;
            easing.percentage = p.lifetime / p.distance;
            float easedPercentage = easing.easeOutElastic();

            float targetX = Math::lerp(p.x, p.x + p.vx * delta, easedPercentage);
            float targetY = Math::lerp(p.y, p.y + p.vy * delta, easedPercentage);

            p.x = Math::lerp(p.x, targetX, easedPercentage);
            p.y = Math::lerp(p.y, targetY, easedPercentage);

            p.lifetime -= delta;
            p.opacity -= delta * 0.3f;
        }

        // Delete particles that have reached the end of their lifetime
        particles.erase(std::remove_if(particles.begin(), particles.end(),
            [](const Particle& p) { return p.lifetime <= 0; }), particles.end());

        // Limit the size of particle vector (just in case)
        if (particles.size() > 500)
        {
            particles.resize(500);
        }
    }


    void drawParticles() 
    {
        for (const auto& p : particles)
        {
            Vector2<float> center(p.x + p.size * 0.5f, p.y + p.size * 0.5f);
            float radius = p.size * 0.5f;
            int segments = 100;

            ImRenderUtil::fillCircle(center, radius, p.color, p.opacity, segments);
        }
    }
};

class ParticleEngine
{
public:
    struct Particle {
        float x, y, vx, vy, lifetime, opacity, size, distance, delta;
        UIColor color;

        Particle() : x(0), y(0), vx(0), vy(0), lifetime(0), opacity(0), color(UIColor()), size(0), distance(0), delta(0) {}
        Particle(float x, float y, float vx, float vy, float lifetime, float opacity, UIColor color, float size, float distance, float delta)
            : x(x), y(y), vx(vx), vy(vy), lifetime(lifetime), opacity(opacity), color(color), size(size), distance(distance), delta(delta) {}
    };

    std::vector<Particle> particles;

    void addParticles(int numParticles, float startX, float startY, float distance, float size, float seconds = 4.f)
    {
        for (int i = 0; i < numParticles; i++)
        {
            Particle p;
            p.x = startX + rand() % 10 - 5;
            p.y = startY + rand() % 10 - 5;
            p.vx = rand() % 200 - 100 + rand() % 10 - 5;
            p.vy = rand() % 200 - 100 + rand() % 10 - 5;
            p.lifetime = seconds;
            p.opacity = 1.0f;
            p.color = ColorUtil::getClientColor(5, 1, 1, p.x * 45);
            p.size = size + rand() % ((int)size / 2 + 1);
            p.distance = distance;
            particles.push_back(p);
        }
    }

    void clearParticles() {
        particles.clear();
    }

    void updateParticles(float delta) {
        for (auto& p : particles) {
            EasingUtil easing;
            easing.percentage = p.lifetime / p.distance;
            float easedPercentage = easing.easeOutElastic();

            float targetX = Math::lerp(p.x, p.x + p.vx * delta, easedPercentage);
            float targetY = Math::lerp(p.y, p.y + p.vy * delta, easedPercentage);

            p.x = Math::lerp(p.x, targetX, easedPercentage);
            p.y = Math::lerp(p.y, targetY, easedPercentage);

            p.lifetime -= delta;
            p.opacity -= delta * 0.3f;
        }

        particles.erase(std::remove_if(particles.begin(), particles.end(),
            [](const Particle& p) { return p.lifetime <= 0; }), particles.end());

        if (particles.size() > 250) {
            particles.resize(250);
        }
    }

    void drawParticles() {
        for (const auto& p : particles) {
            Vector2<float> center(p.x + p.size * 0.5f, p.y + p.size * 0.5f);
            float radius = p.size * 0.5f;
            int segments = 100;

            ImRenderUtil::fillCircle(center, radius, p.color, p.opacity, segments);
        }
    }
};


class ButtonParticle {
public:
    class EasingUtil base;
    Vector2<short> origin;

    ButtonParticle(Vector2<short> origin) {
        this->origin = origin;
        this->base = class EasingUtil();
    }
};

class CustomButton {
public:
	std::vector<ButtonParticle*> particles;
	Vector4<float> pos;
	UIColor Bcolor;
	UIColor Ccolor;
	float alpha;
	class EasingUtil animBase;
	bool BisImage;
	bool CisImage;
	std::string Bimage;
	std::string Cimage;
	std::string FolderPath;


	CustomButton(Vector4<float> rect, UIColor Bcolor, UIColor Ccolor, bool BisImage, std::string Bimage, bool CisImage, std::string Cimage) {
		this->pos = rect;
		this->Bcolor = Bcolor;
		this->Ccolor = Ccolor;
		this->alpha = 1;
		this->animBase = EasingUtil();
		this->BisImage = BisImage;
		this->CisImage = CisImage;
		this->Bimage = Bimage;
		this->Cimage = Cimage;
        this->FolderPath = Util::getClientPath() + "Assets\\";
	}

    void render()
    {
        Vector2<float> res = GuiInfo::ScreenRes;
        Vector2<short> mousePos = GuiInfo::MousePos;

        float delta = RenderUtil::getDeltaTime();

        float offset = animBase.easeOutBounce();
        animBase.incrementPercentage(delta);
        Vector4<float> drawPos = pos.scale(10).lerp(pos, offset);

        RenderUtil::setClipRect(drawPos);

        BisImage ? (RenderUtil::renderImage(FolderPath + this->Bimage, drawPos, Vector2<float>(0.f, 0.f), Vector2<float>(1.f, 1.f), Type::EXTERNAL),
            RenderUtil::flushImage(Bcolor, alpha)) :
            RenderUtil::fillRectangle(drawPos, Bcolor, alpha);

        if (RenderUtil::isMouseOver(this->pos) && Util::leftClick)
        {
            particles.push_back(new ButtonParticle(mousePos));
            animBase.resetPercentage();
            Util::leftClick = false;
        }

        if (!particles.empty())
        {
            float height = this->pos.getWidth();
            std::vector<ButtonParticle*> particlesToRemove;

            for (int i = 0; i < particles.size(); i++)
            {
                ButtonParticle* particle = particles.at(i);
                particle->base.incrementPercentage(delta);
                float ease = particle->base.easeOutExpo();

                float size = Math::lerp(0, height, ease);
                float alpha = Math::lerp(0.5f, 0, ease);
                Vector4<float> finalPos = Vector4<float>(particle->origin.x - size, particle->origin.y - size, particle->origin.x + size, particle->origin.y + size);

                CisImage ? (RenderUtil::renderImage(FolderPath + this->Cimage, finalPos, Vector2<float>(0.f, 0.f), Vector2<float>(1.f, 1.f), Type::EXTERNAL),
                    RenderUtil::flushImage(Ccolor, alpha)) :
                    RenderUtil::fillRectangle(finalPos, Ccolor, alpha);

                if (particle->base.isPercentageMax())
                    particlesToRemove.push_back(particle);
            }

            for (ButtonParticle* part : particlesToRemove)
            {
                particles.erase(std::remove(particles.begin(), particles.end(), part));
            }
        }

        RenderUtil::resetClipRect();
    }
};
