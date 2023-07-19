#type vertex
#version 330 core

struct VsOutput {
    vec2 texCoords;
    vec3 vertexNormal;
    vec3 recalculatedNormal;
    vec3 fragmentPos;
};

#attributes
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
#attributes_end

//shader params
uniform mat4 uViewProjMatrix;
uniform mat4 uModelMatrix;

out VsOutput vsOutput;

void main() {
    gl_Position = uViewProjMatrix * uModelMatrix * vec4(aPos, 1.0);

    vsOutput.texCoords = aTexCoords;
    vsOutput.vertexNormal = aNormal;
    vsOutput.recalculatedNormal = mat3(transpose(inverse(uModelMatrix))) * aNormal;
    vsOutput.fragmentPos = vec3(uModelMatrix * vec4(aPos, 1.0f));
}

#type fragment
#version 330 core

#define AMBIENT_STRENGTH 0.005

struct VsOutput {
    vec2 texCoords;
    vec3 vertexNormal;
    vec3 recalculatedNormal;
    vec3 fragmentPos;
};

struct DirectionalLight {
    vec3 diffuse;

    vec3 direction;
};

#define MAX_POINT_LIGHTS 20
struct PointLight {
    vec3 diffuse;

    vec3 position;
    float radius;
};

#define MAX_SPOT_LIGHTS 20
#define OUTER_CUTOFF_ANGLE_INCREMENT 10
struct SpotLight {
    vec3 diffuse;

    vec3 position;
    vec3 direction;
    float cutoffAngle;
    float radius;
};

struct MaterialData {
    sampler2D diffuse;
};

//vertex shader output
in VsOutput vsOutput;

//lighting
uniform DirectionalLight uDirLight;

uniform PointLight uPointLights[MAX_POINT_LIGHTS];
uniform int uPointLightsCount;

uniform SpotLight uSpotLights[MAX_SPOT_LIGHTS];
uniform int uSpotLightsCount;

//material
uniform MaterialData matData;

//shader params
uniform vec3 uViewPos;
uniform bool uIsLit;

//output
out vec4 FragColor;

float DegToRad(float deg) {
    return deg * 0.01745329251994329576923690768489;
}

vec4 CalculateDirectional(vec4 sampledFragment) {
    float lightDot = max(dot(vsOutput.vertexNormal, -uDirLight.direction), 0.0);

    return vec4(uDirLight.diffuse, 1.0) * lightDot * sampledFragment;
}

vec4 CalculatePointLights(vec4 sampledFragment) {
    vec4 result = vec4(0.0);
    
    for(int i = 0; i < uPointLightsCount; ++i) {
        PointLight light = uPointLights[i];

        vec3 dirToFrag = light.position - vsOutput.fragmentPos;
        float distToFrag = length(dirToFrag);

        vec3 lightDir = normalize(dirToFrag);

        float lightDot = max(dot(vsOutput.vertexNormal, lightDir), 0.0);
        vec3 diffuse = lightDot * light.diffuse;

        float attennuation = 1 / pow(distToFrag / light.radius + 1, 2);
        diffuse *= attennuation;
        
        result += vec4(diffuse, 1.0f) * sampledFragment;
    }

    return result;
}

vec4 CalculateSpotLights(vec4 sampledFragment) {
    vec4 result = vec4(0.0);

    for(int i = 0; i < uSpotLightsCount; ++i) {
        SpotLight light = uSpotLights[i];

        vec3 dirToFrag = light.position - vsOutput.fragmentPos;
        
        float distToFrag = length(dirToFrag);
        vec3 lightDir = normalize(dirToFrag);

        float outerCutoff = light.cutoffAngle + OUTER_CUTOFF_ANGLE_INCREMENT;
        float theta = dot(lightDir, -light.direction);

        float cutoffCos = cos(DegToRad(light.cutoffAngle));
        float outerCutoffCos = cos(DegToRad(outerCutoff));
        float epsilon = cutoffCos - outerCutoffCos;

        if (theta > cutoffCos) {
            float lightDot = max(dot(vsOutput.vertexNormal, lightDir), 0.0);
            float attennuation = 1 / pow(distToFrag / light.radius + 1, 2);

            float intensity = clamp((theta - cutoffCos) / epsilon, 0.0, 1.0);   

            vec4 diffuseColor = vec4(lightDot * light.diffuse * attennuation * intensity, 1.0);

            result += diffuseColor * sampledFragment;
        }
    }

    return result;
}

vec4 CaclulateLighting(vec4 fragment) {
    vec4 result = fragment * AMBIENT_STRENGTH;
    
    result += CalculateDirectional(fragment) + CalculatePointLights(fragment) + CalculateSpotLights(fragment);

    return result;
}

void main() {
    vec4 fragment = texture(matData.diffuse, vsOutput.texCoords);
    if (fragment.a < 0.1) {
        discard;
    }

    if (uIsLit) {
        FragColor = CaclulateLighting(fragment);
        return;
    } else {
        FragColor = fragment;
        return;
    }
}