#include "log.h"
#include "sinoscope.h"

int sinoscope_opencl_init(sinoscope_opencl_t* opencl, cl_device_id opencl_device_id, unsigned int width,
                          unsigned int height) {
    /*
     * TODO
     *
     * Initialiser `opencl->context` du périphérique reçu en paramètre.
     *
     * Initialiser `opencl->queue` à partir du contexte précèdent.
     *
     * Initialiser `opencl->buffer` à partir du context précèdent (width * height * 3).
     *
     * Initialiser `opencl->kernel` à partir du contexte et du périphérique reçu en
     * paramètre. Utilisez la fonction `opencl_load_kernel_code` déclaré dans `opencl.h` pour lire
     * le code du noyau OpenCL `kernel/sinoscope.cl` dans un tampon. Compiler le noyau
     * en ajoutant le paramètre `"-I " __OPENCL_INCLUDE__`.
     *
     * Vous pouvez utiliser la fonction `opencl_print_device_info` pour obtenir de l'information
     * à propos de la compilation de votre noyau OpenCL.
     */
    cl_int error = 0;
    // cl_platform_id platform;

    // error = clGetPlatformIDs(1,&platform,NULL);
    // if(error != CL_SUCCESS) { printf("Error getting platform ID\n"); return error;}
    opencl->context = clCreateContext(0, 1, &opencl_device_id, NULL, NULL, &error);   
    if(error != CL_SUCCESS) { printf("Error creating context\n"); return error;}
    opencl->queue = clCreateCommandQueueWithProperties(opencl->context, opencl_device_id, 0, &error);
    if(error != CL_SUCCESS) { printf("Error creating command Queue\n"); return error;}


    opencl->buffer = clCreateBuffer(opencl->context, CL_MEM_WRITE_ONLY, width*height*3, NULL,  &error);

    size_t size = 0;
    char* src;
    error = opencl_load_kernel_code(&src, &size);
    if(error != CL_SUCCESS || src ==NULL) { printf("Error Loading Kernel\n"); goto fail_free_src;}

    cl_program pgm = clCreateProgramWithSource(opencl->context, 1, (const char **) &src,&size, &error);
    if(error != CL_SUCCESS) { printf("Error Creating Program\n"); goto fail_free_src;}

    error = clBuildProgram(pgm, 1, &opencl_device_id, "-I " __OPENCL_INCLUDE__, NULL, NULL);
    if(error != CL_SUCCESS) { printf("Error %d while Building Program\n", error); 
        opencl_print_build_log(pgm, opencl_device_id);
        goto fail_free_src;
    }

    opencl->kernel = clCreateKernel(pgm,"sinoscope_kernel",&error);
    if(error != CL_SUCCESS) { printf("Error %d while Creating Kernel\n", error); goto fail_free_src;}

fail_free_src:
    free(src);
    return error;

}

void sinoscope_opencl_cleanup(sinoscope_opencl_t* opencl) {
    /*
     * TODO
     *
     * Libérez les ressources associées à `opencl->context`, `opencl->queue`,
     * `opencl->buffer` et `opencl->kernel`.
     */

    clReleaseKernel(opencl->kernel);
    clReleaseCommandQueue(opencl->queue);
    clReleaseContext(opencl->context);
    clReleaseMemObject(opencl->buffer);

}

/*
 * TODO
 *
 * Déclarez les structures partagées avec le noyau OpenCL si nécessaire selon votre énoncé.
 * Utilisez l'attribut `__attribute__((packed))` à vos déclarations.
 */

int sinoscope_image_opencl(sinoscope_t* sinoscope) {
    if (sinoscope->opencl == NULL) {
        LOG_ERROR_NULL_PTR();
        goto fail_exit;
    }

    /*
     * TODO
     *
     * Configurez les paramètres du noyau OpenCL afin d'envoyer `sinoscope->opencl->buffer` et les
     * autres données nécessaire à son exécution.
     *
     * Démarrez le noyau OpenCL et attendez son exécution.
     *
     * Effectuez la lecture du tampon `sinoscope->opencl->buffer` contenant le résultat dans
     * `sinoscope->buffer`.
     */

    cl_int error = 0;
    error = clSetKernelArg(sinoscope->opencl->kernel,0,sizeof(cl_mem),&sinoscope->opencl->buffer);


	error = clSetKernelArg(sinoscope->opencl->kernel, 1, sizeof(int), &(sinoscope->width));
    error |= clSetKernelArg(sinoscope->opencl->kernel, 2, sizeof(int), &(sinoscope->height));
	error |= clSetKernelArg(sinoscope->opencl->kernel, 3, sizeof(int), &(sinoscope->taylor));
	error |= clSetKernelArg(sinoscope->opencl->kernel, 4, sizeof(int), &(sinoscope->interval));
	error |= clSetKernelArg(sinoscope->opencl->kernel, 5, sizeof(float), &(sinoscope->interval_inverse));
	error |= clSetKernelArg(sinoscope->opencl->kernel, 6, sizeof(float), &(sinoscope->time));
    error |= clSetKernelArg(sinoscope->opencl->kernel, 7, sizeof(float), &(sinoscope->max));
	error |= clSetKernelArg(sinoscope->opencl->kernel, 8, sizeof(float), &(sinoscope->phase0));
	error |= clSetKernelArg(sinoscope->opencl->kernel, 9, sizeof(float), &(sinoscope->phase1));
	error |= clSetKernelArg(sinoscope->opencl->kernel, 10, sizeof(float), &(sinoscope->dx));
	error |= clSetKernelArg(sinoscope->opencl->kernel, 11, sizeof(float), &(sinoscope->dy));
    
    if(error != CL_SUCCESS) { printf("Error Setting Kernel Args\n"); return error;}

    // const size_t wg_size = (size_t) sinoscope->width;
    const size_t total_size = sinoscope->width * sinoscope->height; //One dimension enqueueing, total size is only the first dimension

    error = clEnqueueNDRangeKernel(sinoscope->opencl->queue, sinoscope->opencl->kernel, 1, NULL, &total_size, NULL, 0, NULL, NULL);
    if(error != CL_SUCCESS) { printf("Error : %d while Enqueuing NDR Range Kernel\n", error); return error;}


    error = clFinish(sinoscope->opencl->queue);
    if(error != CL_SUCCESS) { printf("Error : %d while Waiting for Queue Finish\n", error); return error;}

    error = clEnqueueReadBuffer(sinoscope->opencl->queue, sinoscope->opencl->buffer, CL_TRUE, 0, sinoscope->buffer_size, sinoscope->buffer, 0, NULL, NULL);
    if(error != CL_SUCCESS) { printf("Error Enqueueing Read Buffer\n"); return error;}


    return error;

fail_exit:
    return -1;
}
