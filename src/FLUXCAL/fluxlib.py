#!/usr/bin/python3

import xarray as xr 
import numpy as np
import pandas as pd
import re
import numpy.matlib as npm
from matplotlib import colors
import plotly.graph_objects as go 
from plotly.subplots import make_subplots
import matplotlib.pyplot as plt
from scipy import optimize
import json
import random as rd

def read_mgrid(filename,*args):
    """
    Función que toma la salida de *.nc de VMEC y genera un archivo de coordenadas que tiene el ángulo toroidal como coordenada
    principal.
    """
    file = xr.open_dataset(filename)

    nr = int(file.ir)
    nz = int(file.jz)
    nphi = int(file.kp)
    nfp = int(file.nfp)
    nextcur = int(file.nextcur)

    rmin = file.rmin
    rmax = file.rmax
    zmin = file.zmin
    zmax = file.zmax
    curlabel = file.coil_group
    

    br = np.zeros(shape=(nr,nz,nphi,nextcur))
    bphi= np.zeros(shape=(nr,nz,nphi,nextcur))
    bz = np.zeros(shape=(nr,nz,nphi,nextcur))
    bx = np.zeros(shape=(nr,nz,nphi,nextcur))
    by = np.zeros(shape=(nr,nz,nphi,nextcur))

    for i in range(0,nextcur):
        br[:,:,:,i] = np.array(file['br_%03d' % (i+1)]).T
        bphi[:,:,:,i] = np.array(file['bp_%03d' % (i+1)]).T
        bz[:,:,:,i] = np.array(file['bz_%03d' % (i+1)]).T
    
    phi = np.arange(start = 0, stop = 2*np.pi/nfp, step = 2*np.pi/(nfp*nphi))    
    raxis = np.linspace(rmin, rmax, num = nr, endpoint = True)
    zaxis = np.linspace(zmin, zmax, num = nz, endpoint = True)

    for k in range(1,nphi):
        bx[:,:,k,:] = np.multiply(br[:,:,k,:],np.cos(phi[k]))-np.multiply(bphi[:,:,k,:],np.sin(phi[k]))
        by[:,:,k,:] = -np.multiply(br[:,:,k,:],np.sin(phi[k]))+np.multiply(bphi[:,:,k,:],np.cos(phi[k]))

    ds = xr.Dataset({
        'br': xr.DataArray(
                data = br, 
                dims = ['nr','nz','nphi','nextcur'],
            ),
        'bphi': xr.DataArray(
                data = bphi, 
                dims = ['nr','nz','nphi','nextcur'],
            ),

        'bx': xr.DataArray(
                data = bx, 
                dims = ['nr','nz','nphi','nextcur'],
            ),
        
        'by': xr.DataArray(
                data = by, 
                dims = ['nr','nz','nphi','nextcur'],
            ),

        'bz': xr.DataArray(
                data = bz, 
                dims = ['nr','nz','nphi','nextcur'],
            ),

        'nfp':nfp, 

        'raxis': xr.DataArray(
                data = raxis,
                dims = ['R']
        ),

        'zaxis': xr.DataArray(
                data = zaxis,
                dims = ['Z']
        ),

        'phi': xr.DataArray(
                data = phi,
                dims = ['phi']
        ),

        'rmin':rmin, 
        'rmax':rmax, 
        'zmin':zmin,
        'zmax':zmax,

        'curlabel': xr.DataArray(
            data = curlabel
            )
    })

    return ds
