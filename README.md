# RayTracingCPP
A backwards ray tracer developed using C++

# About
This project was an assignment for CSCI4471(Computer Graphics) at Saint Mary's University. The task was to develop a Ray Traced image using C++. My objective was to create a realistic looking image using the backward ray tracing technique. To achieve this I knew I had to implement a form of reflective surface for the light to interact with. I found the ScrathAPixel reference on Reflection and refraction extremely helpful. Although, the scope of this task was far more difficult than I thought it would be. </br> 

I started the project with a lab assignment that was provided, this had some starter code and had some of my previous code. However, I quickly realized that it would not be easy to add new features after I got close to a finished product. I also had issues with the OpenCV and Eigen files it relied on. So I decided to start from scratch. I originally planned on using other GNU licensed libraries but I figured it would be a simple program that wouldn't use them efficiently. With help from the resources below and lecture slides, specifically 3.2 and 3.1, I did it. </br>

The last day was spent fixing an issue with the reflections, as I had the normal vectors for the surfaces pointing the wrong way, this led to color issues and lighting problems too. The biggest hurdle however was attempting to map a texture to a plane, which I could not overcome. I plan on completing this outside of this assignment submission time and hope to have it ready in time for the demo (even if it isn't worth any marks). </br>

Currently the program can illustrate any number of spheres with any number of material properties (excluding textures for now). Spheres can be reflective or translucent, or a combination of both. I also have point light sources which are just spheres that emit a color in their intersection surface normal.</br>

I am happy with where it is right now and as mentioned previously have a few plans on more things to add. This was a very fun project and I learned so much about the ray tracing algorithm. It really makes me appreciate the technology we have today. The fact that modern graphics cards can render thousands of ray traced images a minutes or that we have software that can 3d model  so easily is amazing. Thank you Dr. Poovvancheri for the opportunity. </br></br>

# Progress
Working!</br>
About 90% complete...

# External Sources
"Ray Tracing In One Weekend" - Peter Shirley \
-- https://raytracing.github.io/books/RayTracingInOneWeekend.html \
"Fundementals of Computer Graphics" (4th ed.) - Peter Shirley, and Steve Marschner 

"Introduction to Shading Normals"\
-- https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/shading-normals \
"Reflection, Refraction (Transmission) and Fresnel" \
-- https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel \
"Ray Tracing from The Ground Up" - Kevin Suffern 
