# Technical Art Direction in AI

## Lecture sheet: moving from "vibes" to physics-based prompt engineering

**Source:** `Moving from Vibes to Physics-Based Prompt Engineering-4.pdf`  
**Author shown in the deck:** Saad Ahmed  
**Deck title:** *Technical Art Direction in AI: Moving from "Vibes" to Physics-Based Prompt Engineering*  
**Coverage:** 55 pages  
**Audience:** IUT undergraduate students and early creative technologists learning to direct AI-generated visual work  
**Prepared:** 2026-09-19

> Central idea: a visual prompt becomes more controllable when it describes a scene as a system of objects, materials, camera geometry, lighting, environment, editorial intent, and constraints. The deck calls this a move from vague aesthetic adjectives to technical art direction.

## 1. Learning objectives

By the end of this lecture, a student should be able to:

- Decode a creative brief before writing an image prompt.
- Explain the purpose of a brand guideline and connect it to image-generation direction.
- Distinguish vague "vibe" words from observable visual or physical properties.
- Construct a seven-layer prompt using subject, material physics, camera, lighting, atmosphere, mood, and constraints.
- Use basic optics, photometry, material, and human-interaction vocabulary in a prompt.
- Explain why prompt order can help, while recognizing that order is a model-dependent heuristic rather than a guaranteed priority system.
- Design a prompt that specifies grip geometry instead of merely saying "holding."
- Diagnose a weak image without rewriting the entire prompt.
- Iterate surgically by changing one variable at a time.
- Evaluate output quality separately for subject identity, composition, material, lighting, anatomy, text, brand consistency, and physical plausibility.
- Create a fictional brand identity, mission and vision, and two posters using the method.

## 2. One-page lecture summary

### The problem with "vibe" prompting

Words such as `cinematic`, `stunning`, `hyperrealistic`, `luxury`, and `8k` communicate intention, but they leave many scene variables unspecified. A model may respond with a visually attractive image that has the wrong object, wrong material, wrong camera, impossible hand anatomy, inconsistent lighting, or unreadable text.

The deck's proposed response is to replace vague adjectives with descriptions that are more observable:

- What exact object is present?
- What is it doing?
- What is it made of?
- How should light interact with it?
- What camera is observing it?
- What environmental particles or motion are present?
- What must not appear?

### The brief-to-image pipeline

`business context -> brand and audience -> visual direction -> structured prompt -> generated image -> inspection -> one-variable iteration`

### The C.O.R.E.S. brief-decoding method

The deck presents four visible brief questions under the name C.O.R.E.S.:

1. **Context - the why:** business trigger, ultimate objective, and current state.
2. **Objectives and constraints - the what:** scope, deliverables, hard limits, and mandatories.
3. **Recipients - the who:** core persona, pain points, and desired action.
4. **Execution and vibe - the feel:** brand personality, emotional takeaway, and competitive landscape.

The deck calls this C.O.R.E.S., but only four numbered blocks are visibly defined. The final `S` is not separately explained. It may be intended to represent style, but this should be treated as an interpretation rather than a confirmed expansion of the acronym.

### The seven-layer prompt stack

1. **Hero subject:** exact object, identity, geometry, pose, and action.
2. **Material physics:** surface behavior, texture, reflectance, viscosity, condensation, scattering, and imperfections.
3. **Composition and camera geometry:** lens, focal length, aperture, angle, distance, focus, and framing.
4. **Lighting logic:** key, fill, rim, direction, color temperature, intensity, and modifiers.
5. **Atmosphere and motion:** particles, haze, mist, weather, shutter-speed cues, and movement.
6. **Mood and editorial intent:** color grading, magazine style, brand feeling, and narrative direction.
7. **Constraints:** negative prompts, exclusions, anatomy requirements, text requirements, and technical prohibitions.

### The master formula

```text
[subject + action]
+ [material physics]
+ [camera lens / angle]
+ [lighting setup]
+ [atmosphere]
+ [mood]
+ [constraints]
```

The most important practical rule is not that every prompt must contain every word. It is that each important visual decision should be explicit enough to inspect and revise.

## 3. Deck map

| Page range | Cluster | Main purpose |
|---|---|---|
| 1-11 | Brief and brand foundations | Understand why the visual exists, who it serves, and what rules govern it |
| 12-15 | Technical art direction | Introduce the shift from vibe words to a seven-layer prompt structure |
| 16-24 | Physics-based visual vocabulary | Subject geometry, material behavior, camera, lighting, atmosphere, mood, and constraints |
| 25-28 | Prompt priority and troubleshooting | Use a realism hierarchy and put mood after technical foundations |
| 29-37 | Style, color, and contrast | Narrative editorial styles, film/digital grading, dynamic range, and keyword banks |
| 38-40 | Material and human-detail cues | Shader language, surface properties, skin detail, and realism cues |
| 41-47 | Interaction and grip architecture | Convert vague hand-object relationships into explicit grip geometry |
| 48-50 | Lighting, constraints, and iteration | Three-point lighting, negative constraints, and one-variable refinement |
| 51-53 | Master prompt and comparison | Combine the method in a BMW example and compare model outputs |
| 54-55 | Assignment and close | Create a fictional brand identity and visual campaign |

## 4. Foundational concepts

### 4.1 Creative brief

A **creative brief** is a compact description of why a communication or design project exists, what it must accomplish, whom it serves, what it must contain, and how it should feel.

It prevents a common failure: producing a visually attractive deliverable that solves the wrong problem.

### 4.2 Brand guideline

A **brand guideline** is a rulebook for how a brand presents itself across touchpoints. It can specify:

- Logo use and clear space.
- Typography and hierarchy.
- Color palette and contrast.
- Photography and illustration style.
- Voice, tone, and vocabulary.
- Layout, iconography, and composition.
- Social-media and motion conventions.
- Legal, accessibility, and usage requirements.

The deck emphasizes that without a guideline, a brand becomes a disconnected collection of fonts, colors, images, and messages. In AI generation, the guideline becomes a source of constraints and style references, not merely a list of adjectives.

### 4.3 Technical art direction

**Technical art direction** is the translation of creative intent into controllable scene variables. It does not mean removing taste from the process. It means converting taste into specifications that a human or a model can inspect:

```text
"Make it premium"
-> deep shadow density, controlled highlights, solid materials,
   restrained palette, clean composition, precise typography
```

### 4.4 Physics-based prompt engineering

In this deck, **physics-based prompt engineering** means using vocabulary associated with geometry, optics, material response, light transport, motion, and physical interaction to make a visual description more specific.

Important qualification: a text-to-image model does not automatically run a physically accurate renderer just because a prompt contains words such as `refractive index`, `anisotropy`, or `subsurface scattering`. Those words function as learned semantic cues. They may improve the image because the model has seen them associated with certain visual patterns, but the generated scene is not guaranteed to obey the corresponding equations.

## 5. Page-by-page lecture notes

## Page 1 - Understanding the Brand

### What the page shows

The opening page is titled **Understanding the Brand** and credits **Saad Ahmed**. It uses a stylized cat image as the visual anchor.

### Lecture interpretation

The deck begins before prompt writing. This is intentional: a strong image direction starts with understanding the brand and communication problem, not with choosing decorative keywords.

## Page 2 - The C.O.R.E.S. method

### What the page says

The page calls the method **The C.O.R.E.S. Method** and describes it as a way to decode, structure, and challenge a client brief before beginning creative work.

The first visible layer is **Context - the why**.

### Core lesson

Do not accept a requested deliverable as the true problem until the business context has been investigated.

## Page 3 - Context: the why

### Questions from the page

- **Business trigger:** What recent event prompted the project? Examples include a new competitor, a product launch, or declining sales.
- **Ultimate objective:** If the project is wildly successful, what business metric changes?
- **Current state:** What is the client doing now, and why is it failing?

### Example from the deck

A client may say, "We need a new website," while the underlying problem is that the existing site is hard to navigate and has an 80% bounce rate.

### Prompting consequence

Context influences the image's job. A luxury product hero image for a conversion page, an editorial image for brand awareness, and an onboarding illustration may depict the same product but require different composition, emotion, and call-to-action support.

## Page 4 - Objectives and constraints: the what

### Questions from the page

- **Scope and deliverables:** What exact formats, sizes, and platforms are expected?
- **Hard constraints:** What absolute limits exist, such as budget caps, launch dates, or legacy software integration?
- **Mandatories:** What must be included, such as logos, legal disclaimers, or brand colors?

### Important correction

The slide typography appears to read **Objects & Constraints**, but the bullet content clearly points to **Objectives and Constraints**. The lecture interpretation uses the intended meaning.

### Prompting consequence

Output size, aspect ratio, safe text area, logo placement, visual hierarchy, and required copy belong in the brief before they are translated into a generation prompt.

## Page 5 - Recipients: the who

### Questions from the page

- **Core persona:** Who is the primary user? The page asks students to move beyond "women 18-35" toward a richer description such as time-poor millennial mothers who prioritize organic ingredients.
- **Pain points:** What problem does the audience have that the design or product solves?
- **Desired action:** What should the audience do after seeing or interacting with the design?

### Lecture interpretation

Demographics alone rarely determine visual direction. Time pressure, anxieties, aspirations, trust level, and desired action are more useful for choosing visual tone and composition.

## Page 6 - Execution and vibe: the feel

### Questions from the page

- **Brand personality:** If the brand were a person, how would it speak and dress?
- **Emotional takeaway:** Should the audience feel reassured, excited, urgent, or calm?
- **Competitive landscape:** Should the brand blend into industry standards or disrupt them?

The page explicitly argues that "make it pop" is not an adequate art direction. Feelings must be translated into visual language.

### Example translation

```text
"Calm, premium, trustworthy"
-> quiet composition, negative space, soft directional light,
   restrained colors, clean material edges, minimal visual noise
```

## Page 7 - Brand guideline divider

This page is a section divider titled **Brand Guideline** with a stylized cat image. Its role is structural rather than instructional.

## Page 8 - What a brand guideline is

### What the page says

A brand guideline, also called a brand style guide, is described as a rulebook controlling how the brand presents itself across every touchpoint:

- A logo on a physical clothing tag.
- The tone of voice in an Instagram reel.
- Typography on an invoice from a marketing agency.

Without it, fonts, colors, and messaging become disjointed, confuse customers, and dilute trust.

### Prompting consequence

An AI visual prompt should not be treated as an isolated image request. It should be consistent with the brand system, including typography, color, visual density, audience, and emotional promise.

## Page 9 - Behance link

The page contains a **Behance Link** label but does not expose a specific URL in the extracted or visible page content.

### Lecture interpretation

Behance can function as a moodboard and reference source, but reference images should be analyzed rather than copied blindly. Extract:

- Subject scale.
- Color relationships.
- Negative-space pattern.
- Camera height and crop.
- Lighting direction.
- Texture and finish.
- Typography and layout rhythm.

## Page 10 - Fifteen-minute prompt exercise

The page asks students to **write down an image prompt** and gives a time limit of **15 minutes**.

### Suggested way to run the exercise

Write two prompts for the same object:

1. A baseline prompt using only broad vibe words.
2. A structured prompt using the seven-layer stack.

Generate several outputs from both versions and record what changed. The exercise should compare controllability, not just which image looks prettier.

## Page 11 - Fifteen-minute prompt exercise with visual reference

The page repeats the 15-minute prompt exercise and displays a stylized automotive poster as a visual reference.

### Lecture interpretation

The reference image suggests that a prompt must control both the hero object and the surrounding editorial composition. A student should ask:

- What is the hero object?
- What is the camera position?
- What is the light source?
- What makes the image feel like a poster instead of a plain photograph?
- Where would text and logos be placed?

## Page 12 - Technical Art Direction in AI

### What the page introduces

The main title is **Technical Art Direction in AI: Moving from "Vibes" to Physics-Based Prompt Engineering**.

### Lecture interpretation

This is the transition from brand strategy into the operational method for writing image prompts.

## Page 13 - Why prompts are failing

### The three-column comparison

| Column | Message |
|---|---|
| The Old Way | Use vibe words such as cinematic, stunning, hyperrealistic, and 8k |
| The New Way | Use physics and engineering language |
| The Hard Truth | AI models are trained on captioned photography datasets; they do not understand beauty in a human sense, but they may respond to learned associations around terms such as refractive index and 85mm lens compression |

### Technical qualification

The phrase "the model understands refractive index" is pedagogical shorthand. More precisely, a generative model learns statistical associations between text tokens and visual patterns. It may produce glass-like highlights or water-like behavior when prompted with optical vocabulary, but it is not necessarily calculating a physically correct refractive index.

## Page 14 - Prompt hierarchy: order determines priority

### What the page says

The page introduces the **Prompt Hierarchy**, calls it the **7-Layer Stack**, and states that order determines priority. It warns that if physics terms are placed at the end, the model may ignore them.

### Qualification

Ordering important information early is a useful prompting heuristic because it makes the specification easier for both the model and the human to parse. It is not a universal guarantee. Actual behavior depends on the model, tokenizer, prompt weighting system, interface, reference images, negative-prompt handling, and generation settings.

## Page 15 - The seven-layer stack

The page lists the seven layers:

1. **Hero subject:** geometry and action.
2. **Material physics:** surface behavior and textures.
3. **Composition:** camera lens and angle.
4. **Lighting logic:** the virtual studio setup.
5. **Atmosphere:** environmental particles and motion.
6. **Mood/style:** editorial intent.
7. **Constraints:** what to exclude.

### Recommended writing order

Write from concrete scene identity toward interpretation:

```text
what it is -> what it is made of -> how it is seen -> how it is lit
-> what surrounds it -> how it should feel -> what must not happen
```

## Page 16 - Hero subject and action: the geometry

### What the page says

Use specific model names, exact materials, and ergonomic actions. Examples include:

- A 1960s Leica M3 camera.
- A matte-titanium fountain pen.
- A human hand performing a tripod grip.

### Lecture interpretation

The subject layer answers:

- What is the object?
- What exact version or model is it?
- What is its orientation?
- What is it doing?
- What body or mechanism is interacting with it?

Specific nouns reduce ambiguity. A product name can carry visual identity, but brand references should be checked for accuracy and legal use.

## Page 17 - Material physics: the shader

### What the page says

Material physics is described using surface tension, micro-texture, light interaction, and viscosity. Examples are grouped into liquids, metals, and skin:

- **Liquids:** 0.5 mm micro-condensation, vertical gravity streaks, high-tension meniscus.
- **Metals:** anisotropic brushed-steel grain and specular edge highlights.
- **Skin:** visible 0.1 mm pores, subsurface scattering, and natural skin-oil sheen.

### Technical interpretation

The prompt is trying to specify the material's response to light rather than merely naming its color.

| Material cue | Visual consequence |
|---|---|
| Roughness | Broad or sharp highlights; matte versus glossy appearance |
| Metallic behavior | Strong, colored reflections and conductive-looking surfaces |
| Micro-texture | Fine-scale variation that prevents a surface from looking synthetic |
| Condensation | Small droplets, contact with a cooler surface, and gravity-driven streaks |
| Meniscus | Curved liquid boundary near a container edge |
| Anisotropy | Direction-dependent highlights, common in brushed metal and some hair-like structures |
| Subsurface scattering | Light entering and diffusing through translucent material such as skin or wax |

### Qualification

Subsurface scattering is not a universal liquid descriptor. For water and glass, transmission, refraction, reflection, absorption, and volume effects are usually more relevant. In an image prompt, the term may still act as a learned visual cue, but the physical interpretation should remain accurate.

## Page 18 - Composition and camera geometry: the optics

### What the page says

Specify focal length, f-stop or aperture, camera angle, and distance. Examples include:

- **Lens:** 85 mm f/1.2 prime lens, described as a portrait standard.
- **Angle:** worm's-eye view, or a low angle looking upward.
- **Focus:** tack-sharp focus on the foreground logo with shallow depth of field at f/1.8.

### Formal definitions

- **Focal length, `f`:** the optical distance that influences field of view and magnification.
- **Aperture:** the effective opening through which light enters.
- **F-number, `N`:** approximately `N = f / D`, where `D` is the entrance-pupil diameter. A smaller f-number generally means a larger aperture and shallower depth of field, all else equal.
- **Depth of field:** the range of distances that appears acceptably sharp.
- **Camera angle:** the camera's position and orientation relative to the subject.

### Important correction about "lens compression"

Longer lenses are often associated with compressed-looking backgrounds because photographers move farther away to maintain framing. Perspective is primarily determined by relative camera position, not by focal length alone. A technically precise prompt should specify the intended camera distance and framing as well as the lens.

## Page 19 - Visual examples: camera angles

The page is titled **Visual Examples (Angles)** and shows portrait images illustrating different camera and composition choices.

### Discussion questions

- Which image feels dominant or powerful?
- Which image feels intimate or observational?
- How does camera height change the perceived status of the subject?
- How does the crop affect the negative space available for text?

## Page 20 - Lighting logic: the photometry

### What the page says

Lighting direction, color temperature in Kelvin, intensity, and light modifiers are the main variables. The examples are:

- **Key light:** warm 3200 K light from 45 degrees camera-left.
- **Rim light:** cool blue kicker at 6000 K from 170 degrees behind to define edges.
- **Fill light:** soft white bounce at 20% intensity to lift shadows.

### Formal definitions

- **Key light:** primary source defining the subject's shape and dominant illumination.
- **Fill light:** secondary illumination that reduces shadow contrast.
- **Rim or back light:** light from behind or behind the side that separates the subject from the background.
- **Color temperature:** a Kelvin-based description of the apparent warmth or coolness of a light source; lower values are conventionally warmer and higher values cooler.
- **Light modifier:** an object or setup that changes size, direction, softness, or diffusion.

## Page 21 - Visual examples: lights

The page is titled **Visual Examples (Lights)** and presents multiple images demonstrating variations in colored and directional lighting.

### Lecture interpretation

The goal is not to memorize one lighting recipe. It is to connect a visual effect to a cause:

```text
soft shadows -> large or diffused source
hard shadow edge -> small or distant source
silhouette separation -> rim or back light
warm/cool contrast -> different color temperatures
```

## Page 22 - Atmosphere and motion: the environment

### What the page says

Specify particulates, shutter speed, and weather effects. Examples include:

- **Particles:** floating dust motes visible in light beams.
- **Motion:** frozen-motion splash using a 1/8000 second shutter-speed cue.
- **Environment:** subtle cinematic haze, volcanic ash, or morning mist.

### Qualification

An image model may treat shutter speed as a learned style cue rather than a physically simulated camera setting. The prompt should also describe the visible result: frozen droplets, motion blur, streaking, or suspended particles.

## Page 23 - Mood and editorial intent: the style

### What the page says

Mood is expressed through color grading, magazine style, and brand aesthetic. Examples include:

- Desaturated earth tones with a Kodak Portra 400 film-stock look.
- High-fashion Vogue editorial style with stark shadows.
- Cyberpunk neon-noir with high-contrast teal and orange.

### Lecture interpretation

Mood is the interpretive layer. It should shape the final treatment without replacing concrete scene instructions.

## Page 24 - Constraints: the safety layer

### Examples from the page

- No CGI gloss, no waxy skin, and no plastic textures.
- No warped text and no lens distortion on product edges.
- No extra fingers and no impossible anatomy.

### Lecture interpretation

Constraints communicate failure modes. They can be expressed as negative prompts, positive requirements, post-generation checks, or editing instructions.

### Important qualification

Negative prompts do not guarantee compliance. Some interfaces do not support a separate negative-prompt field, and exact typography or logos are often better created or corrected in a design tool after image generation.

## Page 25 - The realism priority pyramid

### What the visual shows

The pyramid places the following from bottom to top:

1. Subject.
2. Physics.
3. Camera.
4. Lighting.
5. Constraints.

### Relationship to the seven-layer stack

This is a simplified priority or troubleshooting pyramid. It omits atmosphere and mood because it is focused on realism foundations. It should not be treated as a replacement for the seven-layer stack.

### Practical use

If the subject identity is wrong, changing the color grade will not fix the image. Debug from the base upward:

```text
subject -> material/physics -> camera -> lighting -> constraints
```

## Page 26 - If the image is struggling: look versus realism

### What the visual says

The page contrasts **Look** and **Realism**. The visual message is that a result can have an attractive style while still failing on physical or material credibility.

### Diagnostic lesson

Ask two separate questions:

- Does the image have the intended mood or look?
- Does the object, material, anatomy, camera, and lighting behave plausibly?

An image can score high on one and low on the other.

## Page 27 - Mood and editorial intent divider

This page introduces **Mood and Editorial Intent (The Style)** with a collage-like visual.

### Lecture interpretation

The deck deliberately moves from realism foundations into narrative style after establishing subject, material, camera, and lighting.

## Page 28 - Put mood after the technical foundations

### What the page says

If `moody` appears at the beginning, the AI may make the lighting dark, the physics messy, and the subject vague. By placing it at the end, the prompt says:

> Build a technically perfect product shot, then color-grade it to look moody.

### Qualification

This is a useful ordering principle, not a hard law. A better general rule is to separate scene construction from final treatment and to evaluate whether the model actually obeyed the hierarchy.

## Page 29 - Narrative editorial styles

### Styles and keyword banks

| Style | Intended feeling | Technical phrases in the deck |
|---|---|---|
| Minimalist | Breathable, clean, high-end, serene | Negative space, monastic simplicity, airy composition, muted palette, high-key minimalism |
| High-fashion | Dramatic, avant-garde, intentionally unnatural | High-contrast, avant-garde, stark editorial, theatrical, sharp-edged shadows, glossy finish |
| Grit and realism | Unposed, raw, authentic | Raw documentary style, candid, unpolished, grainy, high-ISO, found lighting, journalistic integrity |
| Luxury and opulence | Expensive, solid, timeless | Statuesque, monolithic, rich textures, deep blacks, golden-hour warmth, classicism |

### Lecture interpretation

These are not physical properties. They are editorial abstractions that become useful only when tied to concrete image decisions.

## Page 30 - Visual examples: minimalist and high-fashion

The page presents visual examples labeled **Minimalist** and **High-Fashion**.

### Comparison questions

- How much negative space is present?
- Are edges soft or theatrical?
- Is the palette restrained or dramatic?
- Is the pose natural, stylized, or intentionally exaggerated?

## Page 31 - Visual examples: grit and realism, luxury and opulence

The page presents visual examples labeled **Grit and Realism** and **Luxury and Opulence**.

### Lecture interpretation

The same subject could be transformed through texture, lighting, color, camera distance, imperfection, and context. Style is a system of choices, not a single adjective.

## Page 32 - Color science and grading

### What the page says

Instead of saying "nice colors," use specific color-grading terminology.

**Analog or film emulation:**

- Kodak Portra 400: warm, natural skin.
- Fujifilm Velvia: saturated greens and blues.
- Kodachrome: vintage 1960s association.
- Technicolor: hyper-saturated mid-century association.

**Digital grading:**

- Teal and orange: modern cinema association.
- Monochromatic: a single color family.
- Desaturated: moody or post-apocalyptic association.
- High-chroma: neon or pop-art association.
- Low-fidelity or lo-fi: aesthetically imperfect.

### Qualification

Film-stock names are shorthand for a visual association, not a guarantee of an exact emulation. A controlled workflow should specify the actual palette, contrast, grain, exposure, and skin-tone requirements as well.

## Page 33 - Visual examples: analog and digital grading

The page shows visual examples for **Analog/Film Emulation** and **Digital Grading**.

### Discussion prompt

Describe each image without using the word `beautiful`. Use measurable or observable language:

- Hue family.
- Saturation or chroma.
- Luminance.
- Contrast.
- Highlight roll-off.
- Shadow density.
- Grain.
- Skin-tone treatment.

## Page 34 - Dynamic range and contrast

### What the page says

Dynamic range and contrast define the "weight" of an image.

- **Low-key:** dark and dramatic; chiaroscuro, heavy shadows, crushed blacks, moody, mysterious.
- **High-key:** bright and optimistic; blown-out highlights, airy, optimistic, clinical, shadowless.
- **Faded/vintage:** raised blacks, low contrast, washed-out, sepia-tinted, vintage-matte finish.

### Technical interpretation

Contrast is not simply "more detail." It describes the separation between tonal values. A high-contrast image can have strong darks and lights; a low-contrast image compresses tones into a narrower range.

## Page 35 - Visual examples: contrast modes

The page shows examples of low-key, high-key, and faded/vintage treatments.

### Practical exercise

Write three versions of the same product prompt that differ only in dynamic range. Keep subject, camera, and lighting direction fixed so that the grading change can be isolated.

## Page 36 - Keyword bank for mood and intent

### Table from the page

| Mood type | Key technical phrases |
|---|---|
| Luxury | Timeless elegance, premium finish, statuesque lighting, deep shadow density |
| Tech/future | Cyberpunk aesthetic, neon-noir, sleek, sterile, clinical-blue tint |
| Nostalgia | Kodak Portra 400 grain, 1970s aesthetics, sun-drenched, nostalgic haze |
| Aggressive/sport | High-action, dynamic tension, grit, sweat-texture, high-contrast, sharp |
| Whimsical/soft | Ethereal, pastel palette, soft-focus edges, dreamlike, gentle glow |

### Prompting lesson

Use a small, coherent group of keywords. Combining every mood bank at once creates conflicting instructions.

## Page 37 - Visual keyword bank

The page shows visual examples for luxury, tech/future, nostalgia, aggressive/sport, and whimsical/soft.

### Evaluation question

Can a viewer infer which words were used from the image? If not, the vocabulary may be too broad, contradictory, or overpowered by other prompt layers.

## Page 38 - Material physics divider

This page introduces **Material Physics (Surface Engineering)** with a close-up fashion image.

### Lecture interpretation

The deck treats materials as engineered visual systems rather than labels such as `blue`, `metallic`, or `wet`.

## Page 39 - Prompting the shader

### Three material cues

- **Surface tension:** use phrases such as `0.5 mm micro-condensation` or `high-tension meniscus` for liquid-related visual cues.
- **Anisotropy:** use `linear brushed-metal grain` to suggest directional stretching of highlights across a surface.
- **Subsurface scattering:** use the term for skin and translucent materials where light appears to glow through the surface.

### Rendering analogy

In a physically based renderer, these ideas correspond to material and light-response parameters. In an image prompt, they are descriptive tokens that may guide the model toward a learned appearance.

## Page 40 - Face, lips, and details

The page uses three close-up panels labeled **Face**, **Lips**, and **Details**. It emphasizes:

- Skin texture.
- Visible pores and fine lines.
- Natural imperfections.
- Realistic features and asymmetry.
- Accurate lighting.
- Subtle color variation.
- Natural moisture.
- High-resolution textures.
- Micro imperfections.
- Accurate color and tones.

### Lecture interpretation

Perceived realism often comes from controlled imperfection. Perfectly smooth skin and perfectly clean surfaces can look synthetic. The prompt should specify what kind of imperfection is wanted and avoid turning realism into unwanted blemish exaggeration.

## Page 41 - Competitive analysis: perfume product shot

### What the page shows

The page contains a perfume product image and a prompt. The prompt describes:

- An artistic editorial product shot of a Chanel No. 5 perfume bottle.
- The bottle floating in dark reflective water.
- Pink and white lotus flowers surrounding the bottle.
- An amber-filled glass bottle with warm highlights.
- Water droplets clinging to the surface.
- Gentle ripples and fluid reflections.
- Sunlight, golden flares, and subtle rainbow refractions.
- Soft flower petals contrasting with sharp crystal glass.
- A serene, sensual, iconic mood.

### Analysis using the seven layers

| Layer | Evidence in the prompt |
|---|---|
| Subject | Perfume bottle and lotus flowers |
| Action/state | Floating in reflective water; ripples spreading outward |
| Material physics | Amber liquid, crystal glass, droplets, reflections, refractions |
| Composition | Flowers frame the bottle naturally; bottle is the hero |
| Lighting | Sunlight, warm highlights, golden flares, rainbow refractions |
| Atmosphere | Water, ripples, reflective surface |
| Mood | Serene, sensual, iconic |

### Qualification

The prompt is rich, but it still leaves some variables open: exact camera, focal length, depth of field, logo legibility, waterline, light direction, and text layout. It is a strong editorial description but not yet a complete production specification.

The example uses a real brand and product name. Commercial use should respect trademark, advertising, model-release, and platform policies.

## Page 42 - Human interaction: the grip architecture

### What the page says

The page argues that saying **"holding"** is insufficient. Instead, describe grip types and pressure physics.

Examples:

- **Power grip:** fingers wrapped with palm contact.
- **Precision pinch:** thumb and index meet at the tips.

For pressure, the page suggests cues such as skin indentation and blood-displacement paleness at contact points.

### Better interpretation

The model may understand the broad word `holding`, but that word under-specifies contact points, occlusion, finger placement, force, and object orientation. Grip vocabulary makes those relationships explicit.

## Page 43 - Precision pinch

### What the page says

The **Precision Pinch**, also called the **Fine Tech Grip**, is best for jewelry, microchips, needles, small dials, or delicate components.

The physical description is:

- Thumb and index fingertips meet at approximately a 90-degree angle.
- Pad-to-pad contact.
- 90-degree finger flexion.
- Tweezer-like interaction.
- Fingertip pressure.

### Prompt template

```text
The subject is held in a precision pinch: thumb and index fingertips meet
at the tip, forming a controlled tweezer-like grip, with subtle fingertip
pressure and no hidden extra fingers.
```

## Page 44 - Tripod grip

### What the page says

The **Tripod Grip**, also called the **Writing/Stylus Grip**, is best for pens, surgical tools, cosmetic brushes, and styluses.

The physical description is:

- Thumb, index, and middle finger form a triangular support system.
- Three-point stabilization.
- Middle finger acts as a fulcrum.
- Angular finger tension.
- Pencil-hold architecture.

## Page 45 - Power grip or cylindrical wrap

### What the page says

The **Power Grip / Cylindrical Wrap**, also called the **Beverage/Tool Grip**, is best for soda cans, heavy power tools, flashlights, and fitness equipment.

The physical description is:

- Palm makes full contact with the object.
- Fingers wrap around to meet the thumb.
- Full palmar wrap.
- Cylindrical grip.
- Thumb-over-index lock.
- Closed-fist interaction.

One of the small example labels on the page is visually incomplete, so the sheet preserves the clear grip concepts rather than inventing the missing caption.

## Page 46 - Lateral pinch or key grip

### What the page says

The **Lateral Pinch / Key Grip**, also called the **Thin Object Grip**, is best for car keys, credit cards, slim remote controls, and luxury slim watches.

The physical description is:

- Thumb presses the object against the side of the index finger's second knuckle.
- Lateral pinch.
- Key-turn grip.
- Side-knuckle compression.
- Thumb-pad to the radial side of the index finger.
- Shear-force interaction.

## Page 47 - Support or palmar rest

### What the page says

The **Support / Palmar Rest**, also called the **Electronics Grip**, is best for tablets, books, trays, and smartphones in lifestyle shots.

The physical description is:

- Product rests on an open palm or flattened fingers.
- Gravity does more work than squeeze force.
- Open palmar support.
- Weight-bearing rest.
- Finger splay or natural extension.
- Passive grip architecture.

### Prompting lesson

Not every interaction is a squeeze or wrap. Describing support and load-bearing changes the hand pose, occlusion, and product orientation.

## Page 48 - Lighting logic: the virtual gaffer

### What the page says

The page calls lighting the **number one control lever** and presents the three-point rule:

- **Key light:** defines the shape, for example a 45-degree angle at 5600 K.
- **Rim light:** defines the silhouette, for example a sharp 170-degree backlight.
- **Fill light:** controls shadows, for example a 20% intensity white bounce.

### Lecture interpretation

Lighting changes the visible evidence of form, material, depth, and mood. If an object looks flat, changing the adjective `cinematic` is less useful than asking whether the key, fill, and rim relationships are specified.

### Qualification

Three-point lighting is a widely used creative convention, not a universal rule. Natural scenes, product setups, and editorial work may use different arrangements.

## Page 49 - Constraints: blocking the AI look

### What the page says

Modern models aggressively stylize, so constraints pull the result toward reality.

The essential negatives shown are:

- No plastic or waxy skin.
- No CGI or video-game gloss.
- No warped text or impossible physics.
- No lens distortion on product edges.

### Practical interpretation

Constraints should be tied to observable failure modes. Instead of a generic `make realistic`, use checks such as:

```text
preserve straight product edges;
maintain plausible contact shadows;
avoid waxy skin;
keep text out of the generated image unless exact typography is required;
avoid impossible reflections and duplicate objects
```

## Page 50 - Surgical iteration strategy

### What the page says

Do not rewrite the entire prompt if the image is already 80% correct. Change one variable at a time.

The workflow is:

1. Lock subject and composition.
2. Adjust lighting only.
3. Adjust materials only.

### Why this works

Changing multiple variables destroys causal information. If subject, camera, material, lighting, and mood all change between attempts, you cannot tell which change produced the improvement or the failure.

## Page 51 - The master formula

### Formula shown

```text
[SUBJECT + ACTION]
+ [MATERIAL PHYSICS]
+ [CAMERA LENS / ANGLE]
+ [LIGHTING SETUP]
+ [ATMOSPHERE]
+ [MOOD]
+ [CONSTRAINTS]
```

The page title is visually written as **THE MASTER FORMULAT**, which appears to be an incomplete or misspelled form of **THE MASTER FORMULA**.

### Prompt schema

```yaml
subject_and_action:
  identity: "exact object or person"
  pose_or_action: "what it is doing"
  geometry: "orientation, scale, silhouette"
material_physics:
  surface: "roughness, gloss, grain, pores"
  light_response: "reflection, refraction, scattering"
camera:
  lens: "focal length"
  angle: "camera height and direction"
  aperture: "f-number and depth of field"
lighting:
  key: "direction, color temperature, softness"
  fill: "shadow lift"
  rim: "silhouette separation"
atmosphere:
  particles: "dust, mist, rain, haze"
  motion: "frozen action or blur"
mood:
  editorial_style: "minimalist, luxury, documentary, etc."
  grade: "palette, contrast, grain"
constraints:
  exclude: ["waxy skin", "warped text", "impossible anatomy"]
  required: ["safe logo area", "clear product silhouette"]
```

## Page 52 - Full BMW master prompt

### Subject and action

The example asks for a high-resolution, photorealistic dark metallic sapphire-blue BMW M5 Competition, positioned centrally on a concrete waterfront promenade at bumper level, shown in a front three-quarter view with authoritative presence.

### Material physics

It specifies:

- High-gloss metallic blue paint with intricate reflections.
- Black multi-spoke lightweight alloy wheels.
- Large brake assemblies.
- Precision-carved carbon-fiber splitter and diffuser.
- Clear LED headlight elements with internal glow.
- Concrete and reflective-glass architecture.
- Serene still lake water.
- Imperfect concrete pavement.
- Distant rugged mountains with stone and snow texture.

### Camera lens and angle

The prompt asks for a wide-angle, low-angle hero lens of approximately 24 mm. The camera sits slightly below the grille so the car dominates the frame and the background looks vast.

### Lighting setup

The prompt uses golden hour, a low sun from the far left, a strong warm lens flare, warm atmospheric haze, a sky transitioning from deep orange-gold near the horizon to deep cerulean blue above, and soft diffused clouds.

### Atmosphere

The scene is tranquil, pristine, and clean, with a serene lake, rugged snow-dusted mountains, a clear golden sky, gentle hazy light, and sleek modern architecture.

### Mood

The intended feeling is empowering, luxurious, precisely engineered, authoritative, sophisticated, and connected to high-performance driving heritage.

### Constraints and required text

The prompt asks for all text and logos to be white and perfectly legible:

- Top-center BMW roundel.
- `THE ULTIMATE DRIVING MACHINE`.
- `DRIVEN BY PASSION. BUILT ON PERFORMANCE.`
- Small tri-color M logo slash.
- Front license plate: `THE M5`.
- Four bottom icons and labels: `PRECISION ENGINEERED`, `POWER UNLEASHED`, `LUXURY REDEFINED`, and `LEGACY CONTINUED`.
- Large line: `SHEER DRIVING PLEASURE`.
- Paragraph: `For over a century, BMW has set the standard for performance, innovation, and luxury. Every curve. Every detail. Every drive. This is more than a car. This is BMW.`
- Bottom-center: `BMW.COM`.

### Production qualification

Exact logos, legal slogans, and perfect typography are unreliable in pure text-to-image generation. A production workflow should generate the image with a reserved text-safe layout, then add approved logos and copy in a design tool using authorized brand assets.

## Page 53 - Model comparison

The page compares four generated poster outputs labeled:

- GPT.
- Nano Banana.
- Seedream.
- MAI.

### What can be learned

The page illustrates that different image systems can interpret the same structured direction differently in composition, car placement, typography, logo fidelity, lighting, and poster layout.

### What cannot be concluded

The deck does not provide a controlled benchmark. It does not specify model versions, seeds, settings, number of attempts, post-processing, or evaluation criteria. Therefore, the page is a visual demonstration, not evidence that one model is universally better.

### Better comparison protocol

Keep constant:

- Same prompt.
- Same aspect ratio.
- Same reference images.
- Same number of attempts.
- Same text and logo requirements.
- Same post-processing policy.

Score separately:

- Subject fidelity.
- Composition.
- Material plausibility.
- Lighting coherence.
- Anatomy and object geometry.
- Typography and logo accuracy.
- Brand consistency.
- Editing effort.

## Page 54 - Assignment

The deck asks students to create the following items using AI:

1. An imaginary brand logo.
2. A mission and vision for the imaginary brand.
3. Two posters for the imaginary brand.

### Recommended submission package

- One-page brief using the C.O.R.E.S. questions.
- Mini brand guideline with palette, type direction, personality, and audience.
- Logo concept and usage constraints.
- Mission and vision statements.
- Two seven-layer image prompts.
- Two final posters.
- A comparison showing at least one baseline prompt and one structured prompt.
- A short iteration log describing which single variable changed between versions.

## Page 55 - Thank you

The final page contains a large **Thank you!** message and closes the deck.

## 6. Technical foundations behind the method

### 6.1 Geometry and spatial relationships

Geometry describes where things are, how they are oriented, and how they interact. In prompts, geometry is represented through:

- Position: foreground, background, left, right, center.
- Scale: close-up, medium shot, wide scene.
- Orientation: front-facing, three-quarter, profile, top-down.
- Pose: standing, leaning, crouching, gripping, resting.
- Contact: touching, pressing, floating, suspended, embedded.
- Occlusion: what blocks or overlaps what.

Vague verbs such as `holding` hide many of these variables. A grip description exposes them.

### 6.2 Optics and camera geometry

The field of view of a simple pinhole camera can be related to focal length by:

```text
FOV = 2 arctan(sensor_size / (2f))
```

This is a simplified geometric relationship. In visual prompting, the useful intuition is:

- Shorter focal lengths generally show a wider field of view.
- Longer focal lengths generally show a narrower field of view.
- Camera distance strongly affects perspective and relative size.
- Aperture affects light intake and depth-of-field behavior.
- Camera height changes perceived power, intimacy, and viewpoint.

### 6.3 Lighting and inverse-square intuition

For an idealized point source, illuminance decreases approximately with the square of distance:

```text
E proportional to 1 / r^2
```

Real studio lights are not ideal point sources, and modifiers change the behavior. Still, this explains why moving a light can change falloff and contrast dramatically.

### 6.4 Material response

A physically based rendering workflow often separates or approximates:

- Base color or albedo.
- Metallic behavior.
- Roughness.
- Normal or bump detail.
- Specular response.
- Transmission.
- Index of refraction.
- Subsurface scattering.
- Emission.

A text-to-image model may not expose these as controllable numerical sliders, but the vocabulary can help describe the desired visual response.

### 6.5 Color and contrast

Color direction should specify more than a color name:

- Hue family.
- Saturation or chroma.
- Luminance.
- Warm-cool balance.
- Contrast.
- Highlight and shadow treatment.
- Grain or texture.
- Skin-tone preservation.

### 6.6 Human-object interaction

A believable hand interaction depends on:

- Finger count and identity.
- Joint flexion.
- Contact points.
- Pressure and indentation.
- Object orientation.
- Occlusion.
- Load or support.
- Hand-object scale.

Grip types are useful because they name a repeated geometric pattern rather than a vague action.

## 7. Practical implementation blueprint

### Step 1 - Decode the brief

Complete this table before generating anything:

| C.O.R.E.S. field | Your answer |
|---|---|
| Context and business trigger | Why does this asset need to exist now? |
| Objective | What should change if the asset succeeds? |
| Current state | What exists already, and what is failing? |
| Scope and deliverables | What formats, sizes, channels, and quantities are required? |
| Hard constraints | What cannot change? |
| Mandatories | Which logos, copy, colors, products, or legal elements must appear? |
| Recipient | Who will see it? |
| Pain point | What does the audience care about or struggle with? |
| Desired action | What should the viewer do next? |
| Personality and emotion | How should the brand feel? |
| Competitive position | Blend in or stand out? |

### Step 2 - Convert the brief into a scene specification

```json
{
  "purpose": "launch a premium product campaign",
  "audience": "design-conscious young professionals",
  "subject": {
    "identity": "fictional matte-titanium fountain pen",
    "action": "held in a tripod grip above a paper sketch",
    "orientation": "front three-quarter view"
  },
  "material": {
    "surface": "brushed titanium with directional grain",
    "light_response": "controlled specular edge highlights"
  },
  "camera": {
    "lens": "85mm portrait lens",
    "angle": "slightly elevated three-quarter angle",
    "aperture": "f/2.8 with shallow but usable depth of field"
  },
  "lighting": {
    "key": "soft warm light from camera-left",
    "fill": "low-intensity neutral bounce",
    "rim": "subtle cool rim on the pen edge"
  },
  "atmosphere": "quiet studio, faint paper dust",
  "mood": "minimalist, premium, calm",
  "constraints": [
    "no extra fingers",
    "no warped pen geometry",
    "reserve negative space for headline"
  ]
}
```

### Step 3 - Write the prompt in layers

Avoid combining contradictory style terms. If the mood is both luxury and gritty, define where each belongs: premium material and restrained composition, but documentary grain and natural imperfections.

### Step 4 - Generate a controlled baseline

Record:

- Model and version.
- Prompt text.
- Negative prompt or constraints.
- Aspect ratio and resolution.
- Reference images.
- Seed or generation identifier if available.
- Number of attempts.

### Step 5 - Inspect the result by layer

Use a checklist rather than overall impression:

| Layer | Pass question |
|---|---|
| Subject | Is the exact object or person correct? |
| Action | Is the pose or action unambiguous? |
| Material | Does the surface respond plausibly to light? |
| Camera | Is the angle, crop, and focus useful? |
| Lighting | Can the key, fill, and rim relationships be inferred? |
| Atmosphere | Are particles or motion visible without distracting from the subject? |
| Mood | Does the grade support the brand? |
| Constraints | Are the prohibited artifacts absent? |
| Text | Is all required copy accurate and legible? |

### Step 6 - Iterate surgically

Change one variable per iteration:

1. Lock subject and composition.
2. Fix lighting.
3. Fix material.
4. Fix interaction or anatomy.
5. Fix atmosphere.
6. Apply mood and color grade.
7. Add or repair typography in a design tool.

### Step 7 - Archive the decision

Save the prompt, output, score, change made, and next hypothesis. This turns prompting into an experiment rather than a sequence of untracked guesses.

## 8. Worked mini-projects

### Mini-project A - Premium pen product shot

#### Baseline prompt

```text
A beautiful premium fountain pen, cinematic, luxury, stunning, high quality.
```

#### Structured prompt

```text
Hero subject and action: a matte-titanium fountain pen held by a human hand
in a precise tripod grip above a cream paper sketch, front three-quarter view,
the pen tip angled toward the lower-right corner.

Material physics: directional brushed-titanium grain, restrained satin finish,
sharp but controlled specular highlights along the barrel, subtle natural skin
pores and fingertip pressure at the contact points, paper fibers visible.

Camera: 85mm lens, camera slightly above the desk, f/2.8, pen tip and grip
area tack-sharp, background softly defocused, enough negative space above for
a headline.

Lighting: large warm key light at 45 degrees camera-left, soft neutral fill at
20 percent, subtle cool rim light separating the pen from the background.

Atmosphere: clean quiet studio, faint paper dust in the light beam, no motion blur.

Mood: minimalist premium editorial, calm, precise, high-end stationery campaign.

Constraints: no extra fingers, no warped pen geometry, no plastic gloss, no waxy
skin, no illegible text, no distracting objects in the negative-space area.
```

#### Evaluation

Score each from 1 to 5:

- Pen identity.
- Tripod grip accuracy.
- Titanium material.
- Camera and focus.
- Lighting coherence.
- Brand mood.
- Constraint compliance.

### Mini-project B - Liquid and reflective packaging

#### Design goal

Create a premium fictional skincare bottle floating above dark reflective water.

#### Layer decisions

| Layer | Specification |
|---|---|
| Subject | Amber glass skincare bottle, upright and centered |
| Action/state | Floating just above the water surface with concentric ripples below |
| Material | Transparent glass, amber liquid, micro-condensation, controlled refraction |
| Camera | Low three-quarter angle, 50 mm, shallow depth of field |
| Lighting | Warm key from upper-left, cool rim from behind, soft fill on label area |
| Atmosphere | Morning mist and a few visible droplets |
| Mood | Serene, sensual, premium, botanical |
| Constraints | No melted bottle, no warped label, no impossible reflections, no extra products |

#### Experiment

Generate one version with only `wet` and another with explicit condensation, meniscus, droplets, reflection, refraction, and ripples. Compare whether the material cues become more specific.

### Mini-project C - Hand interaction and technology product

#### Design goal

Show a small microchip held by a precision pinch.

#### Prompt core

```text
A tiny black silicon microchip held in a precision pinch: the thumb and index
fingertips meet at the chip's edges at approximately a 90-degree angle, with
pad-to-pad contact, visible fingertip pressure, natural joint flexion, and a
clear view of the chip surface. Macro lens, shallow depth of field, cool
technical studio lighting, controlled reflections, no extra fingers, no fused
fingertips, no oversized chip, no impossible grip.
```

#### Evaluation

Inspect contact geometry first. A visually beautiful macro image fails if the chip floats, the fingers merge, the object is too large for the hand, or the thumb and index positions are anatomically impossible.

## 9. Experimental learning protocol

The most useful way to learn this topic is to treat prompting as a controlled experiment.

### Hypothesis

Adding explicit material, camera, lighting, and constraint layers will improve controllability compared with a vibe-only prompt.

### Measurement

For ten outputs per condition, score:

- Subject correctness.
- Composition correctness.
- Material plausibility.
- Lighting coherence.
- Anatomy or interaction correctness.
- Text and logo accuracy.
- Brand consistency.
- Human editing time.

### Conditions

1. Vibe-only baseline.
2. Seven-layer structured prompt.
3. Seven-layer prompt plus a reference image.
4. Seven-layer prompt plus one-variable surgical iteration.

### Observation

Record common errors, not only average score:

- Which layer fails most often?
- Does added detail improve or confuse the output?
- Does the model ignore constraints?
- Does more prompt length increase unwanted style drift?
- Does a reference image improve geometry but reduce brand originality?

### Interpretation

If the structured prompt helps subject and material but text remains unreliable, use a hybrid workflow: generate the visual scene, then typeset the text externally.

### Decision

Keep the layers that improve the target metric. Remove decorative words that do not change the result. The goal is controllability and repeatability, not maximal prompt length.

## 10. Common failure modes and engineering fixes

| Failure | Why it happens | Fix |
|---|---|---|
| Attractive but wrong object | Subject identity is underspecified | Name exact object, model, material, orientation, and scale |
| Good mood but weak realism | Mood dominates concrete scene details | Move mood after subject, material, camera, and lighting |
| Plastic or waxy surface | Surface response is vague | Specify roughness, pores, grain, imperfections, and highlight behavior |
| Wrong perspective | Lens is given without camera position | Specify camera distance, height, framing, and focal length |
| Flat lighting | Only "cinematic lighting" is used | Describe key, fill, rim, direction, softness, and color temperature |
| Impossible liquid | Liquid is named without behavior | Add droplets, meniscus, ripples, reflection, refraction, and gravity cues |
| Bad hands | "Holding" leaves contact geometry ambiguous | Use a named grip, finger positions, pressure, and object orientation |
| Distorted text or logos | Generators are weak at exact typography | Reserve a text-safe area and add copy in a design tool |
| Prompt drift | Too many variables change between attempts | Lock the good parts and change one variable |
| Conflicting style terms | Keyword banks are combined without hierarchy | Choose one primary editorial intent and define supporting cues |
| Brand inconsistency | Prompt ignores the brand guideline | Add palette, type, logo, voice, audience, and competitive position |
| False sense of physics | Technical words are treated as guarantees | Inspect the image; use a renderer or post-processing when accuracy matters |

## 11. Exam-oriented quick reference

### Definitions

| Term | Exam-ready definition |
|---|---|
| Creative brief | A structured description of purpose, audience, deliverables, constraints, and intended effect |
| Brand guideline | A rulebook defining consistent visual and verbal brand presentation across touchpoints |
| Technical art direction | Translating creative intention into observable and controllable scene variables |
| Prompt hierarchy | An ordered organization of prompt information intended to reduce ambiguity and improve controllability |
| Hero subject | The main object, person, or visual focus of the composition |
| Material physics | Descriptions of surface, texture, roughness, reflectance, transmission, viscosity, and light interaction |
| Focal length | A camera parameter that influences field of view and framing; perspective also depends strongly on camera distance |
| Aperture or f-number | An optical setting related to light intake and depth-of-field behavior |
| Key light | The primary light that defines the subject's form |
| Fill light | Secondary light that controls shadow density |
| Rim light | Back or back-side light that separates the subject silhouette |
| Atmosphere | Particles, haze, mist, weather, and motion cues surrounding the subject |
| Editorial intent | The narrative and stylistic feeling the image should communicate |
| Constraint | A requirement about what must or must not appear in the output |
| Negative prompt | An explicit instruction describing unwanted objects, artifacts, or styles |
| Surgical iteration | Refining an image by changing one variable while keeping successful variables fixed |
| Precision pinch | A thumb-and-index fingertip grip used for small or delicate objects |
| Tripod grip | A three-point thumb-index-middle-finger grip used for pens, styluses, and tools |
| Power grip | A palm-and-finger wrap used for cylindrical or heavy objects |
| Lateral pinch | A thin-object grip in which the thumb presses against the side of the index finger |
| Palmar rest | A support interaction where the object rests on an open palm or flattened fingers |

### Key distinctions

| Distinction | Correct explanation |
|---|---|
| Vibe versus specification | A vibe expresses an intended feeling; a specification describes the scene variables that can create or test that feeling |
| Physics cue versus physical simulation | A physics term may guide a learned visual association; it does not guarantee physically accurate rendering |
| Lens versus perspective | Focal length changes field of view; camera position and distance largely determine perspective relationships |
| Mood versus lighting | Mood is an editorial interpretation; lighting is a physical or visual setup that contributes to it |
| Negative prompt versus quality control | A negative prompt is an instruction; quality control checks whether the output actually obeyed it |
| More detail versus more control | Extra words help only when they are coherent, relevant, and testable |
| Image generation versus graphic design | Generators are useful for imagery; exact logos, copy, layout, and brand typography often need a design workflow |

### Short-answer questions

1. What problem does the C.O.R.E.S. method solve before prompt writing begins?
2. Explain the seven layers of the prompt stack.
3. Why can the phrase "make it cinematic" be insufficient?
4. What is the difference between a key light, fill light, and rim light?
5. Why is `85mm lens compression` an incomplete technical description?
6. How do material physics cues change a prompt for liquid, metal, or skin?
7. Why should mood often come after subject, material, camera, and lighting?
8. Why is "holding a pen" weaker than "a dynamic tripod grip with three-point stabilization"?
9. What does surgical iteration mean, and why is it useful?
10. Why should exact logos and slogans often be added after image generation?
11. Why is the four-model comparison on Page 53 not a controlled benchmark?
12. How would you measure whether physics-based prompting actually improved an output?

### Design question

> Design a complete AI image-generation workflow for a fictional premium technology brand. Start from the C.O.R.E.S. brief, define the brand guideline, construct a seven-layer prompt, specify the evaluation rubric, and describe a one-variable iteration plan for fixing a material or anatomy failure.

A strong answer must separate brand strategy from scene construction, scene construction from mood, and generation from quality control.

## 12. Assignment rubric

| Criterion | Excellent work demonstrates |
|---|---|
| Brief quality | Clear context, objective, audience, pain point, action, and constraints |
| Brand system | Coherent personality, palette, typography direction, and visual rules |
| Prompt structure | All seven layers are explicit and internally consistent |
| Technical specificity | Camera, material, lighting, atmosphere, and interaction are observable |
| Constraint design | Failure modes are named and checked rather than vaguely excluded |
| Iteration discipline | Only one or a small number of variables change between versions |
| Evaluation | Output is scored by layer, not only by overall attractiveness |
| Production awareness | Logos, text, accessibility, and trademark issues are handled responsibly |
| Reflection | Student explains what failed, why it failed, and what changed |

## 13. Necessary links and sites

Links were checked on 2026-09-19. Model interfaces, documentation, URLs, capabilities, and commercial policies change over time. Use official documentation for current behavior.

**Source labels:** primary research papers explain model and rendering foundations; official platform docs explain current product behavior; educational rendering references explain optics and materials; inspiration platforms provide examples but are not technical authorities.

### A. Image-generation and prompting documentation

- [OpenAI Image Generation API guide](https://developers.openai.com/api/docs/guides/image-generation) - official documentation for image generation and image prompting.
- [OpenAI API documentation](https://developers.openai.com/api/docs) - broader API concepts, image inputs, production, safety, and evaluations.
- [Google Gemini API documentation](https://ai.google.dev/gemini-api/docs) - official Gemini API documentation and model capabilities.
- [Midjourney documentation](https://docs.midjourney.com/hc/en-us) - official documentation for Midjourney prompting and image workflows.
- [Stability AI Developer Platform](https://platform.stability.ai/docs) - official developer documentation for Stability AI tools and APIs.
- [Adobe Firefly text-to-image help](https://helpx.adobe.com/firefly/using/text-to-image.html) - official Adobe guidance for text-to-image workflows.

### B. Primary research on image-text models and control

- [CLIP: Learning Transferable Visual Models From Natural Language Supervision](https://arxiv.org/abs/2103.00020) - explains learning visual representations from image-text pairs and why language can reference visual concepts.
- [High-Resolution Image Synthesis With Latent Diffusion Models](https://arxiv.org/abs/2112.10752) - foundational paper on latent diffusion and text conditioning.
- [ControlNet: Adding Conditional Control to Text-to-Image Diffusion Models](https://arxiv.org/abs/2302.05543) - shows how spatial controls such as edges, depth, segmentation, and human pose can guide diffusion models.
- [OpenAI CLIP code and model reference](https://github.com/openai/CLIP) - implementation reference for the CLIP research project.
- [CompVis latent-diffusion repository](https://github.com/CompVis/latent-diffusion) - research implementation associated with latent diffusion.

### C. Rendering, optics, and material references

- [Physically Based Rendering: From Theory to Implementation](https://pbr-book.org/4ed/contents) - open technical reference on light transport, cameras, materials, sampling, and physically based rendering.
- [Blender Manual](https://docs.blender.org/manual/en/latest/index.html) - official manual for cameras, lights, shader nodes, rendering, and color management.
- [Blender camera documentation](https://docs.blender.org/manual/en/latest/render/cameras.html) - camera types, lenses, perspective, and depth-of-field concepts.
- [Blender light-object documentation](https://docs.blender.org/manual/en/latest/render/lights/light_object.html) - light types and lighting controls in a physically based workflow.
- [Blender Principled BSDF documentation](https://docs.blender.org/manual/en/latest/render/shader_nodes/shader/principled.html) - material parameters such as base color, metallic, roughness, transmission, and subsurface.
- [CIE International Commission on Illumination](https://cie.co.at/) - authoritative color-science organization and terminology reference.

### D. Brand, audience, and accessibility references

- [Behance](https://www.behance.net/) - visual reference and portfolio platform mentioned in the deck; use it for analysis and moodboarding, not uncredited copying.
- [W3C Web Accessibility Initiative](https://www.w3.org/WAI/) - accessibility guidance relevant to contrast, typography, color, and digital brand assets.
- [Web Content Accessibility Guidelines](https://www.w3.org/WAI/standards-guidelines/wcag/) - current WCAG standards and supporting resources.

### E. Workflow and production tools

- [Adobe Photoshop Generative Fill documentation](https://helpx.adobe.com/photoshop/using/generative-fill.html) - useful for hybrid workflows where AI creates imagery and the designer finishes composition and text.
- [Figma](https://www.figma.com/) - layout, brand-system, and poster-composition workflow.
- [Canva](https://www.canva.com/) - accessible layout and brand-template workflow; the source PDF metadata identifies Canva as the creator.
- [GitHub](https://github.com/) - store prompt versions, evaluation logs, and experiment metadata.

## 14. Verification and transcription notes

- The PDF contains 55 pages and is text-extractable. Visual review was used to confirm page layout, image examples, section boundaries, and small captions.
- Page 2 names a C.O.R.E.S. method but visibly defines four numbered blocks. The final `S` is not separately explained; this sheet does not invent a definitive expansion.
- Page 4 visually reads like "Objects & Constraints," but the content is more naturally interpreted as "Objectives and Constraints."
- Page 9 says **Behance Link** but does not expose a specific Behance URL.
- Page 13's claim that AI models "understand" refractive index and 85 mm lens compression is treated as a metaphor for learned visual associations, not as a claim of physical simulation.
- Page 14 says prompt order determines priority. This is retained as the deck's rule of thumb and qualified as model-dependent.
- Page 25 presents a five-level realism pyramid that differs from the seven-layer stack by omitting atmosphere and mood.
- Page 41 contains obvious typographical errors in the extracted prompt, including variants of "Chanel," "perfume bottle," and "floating." The lecture sheet normalizes the meaning while preserving the example's content.
- Page 45 and Page 47 contain a few incomplete small image captions. The clear grip definitions are retained without guessing the missing words.
- Page 51 visually says **THE MASTER FORMULAT**, which appears to be a typo or incomplete form of **THE MASTER FORMULA**.
- Page 52 requests perfect logos, slogans, icons, and text. These requirements are not reliably guaranteed by pure text-to-image generation and should be finished in a design tool for production use.
- Page 53 compares GPT, Nano Banana, Seedream, and MAI, but gives no controlled evaluation protocol. It should be taught as a visual demonstration, not a universal ranking.
- Page 54 is the practical assignment; Page 55 is a closing thank-you page.

## 15. Final takeaway

The deck's most useful principle is not "use more technical words." It is:

> Turn creative intention into a structured scene specification, inspect each layer independently, and change one variable at a time.

The strongest workflow combines three skills:

1. **Strategic understanding:** know why the image exists, who it is for, and what action it should support.
2. **Technical direction:** specify geometry, material, camera, lighting, atmosphere, mood, and constraints.
3. **Experimental iteration:** record outputs, evaluate failure modes, and refine causally.

Physics vocabulary is valuable because it gives the prompt more observable handles. It is not valuable because a keyword can force a generative model to obey the laws of optics. The final standard is a controllable, coherent, brand-appropriate image that survives inspection and can be finished responsibly.
