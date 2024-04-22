import numpy as np
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import sys, pdb, string, random, traceback
sys.path.append('.')
#x = np.linspace(-3, 3, 256)
#y = np.linspace(-3, 3, 256)
#X, Y = np.meshgrid(x, y)
#Z = np.sinc(np.sqrt(X ** 2 + Y ** 2))

#fig = plt.figure()
#ax = fig.gca(projection = '3d')
#ax.plot_surface(X, Y, Z, cmap=cm.gray)
#plt.show()




#N = 50
#x = np.random.rand(N)
#y = np.random.rand(N)
#colors = np.random.rand(N)
#area = (30 * np.random.rand(N))**2  # 0 to 15 point radii

#plt.scatter(x, y, s=area, c=colors, alpha=0.5)
#plt.show()


from scipy.interpolate import LinearNDInterpolator

#import matplotlib.pyplot as plt

if 1==2:
	rng = np.random.default_rng()

	x = rng.random(10) - 0.5

	y = rng.random(10) - 0.5

	z = np.hypot(x, y)
	print(x,y,z)

	X = np.linspace(min(x), max(x))

	Y = np.linspace(min(y), max(y))

	X, Y = np.meshgrid(X, Y)  # 2D grid for interpolation

	interp = LinearNDInterpolator(list(zip(x, y)), z)

	Z = interp(X, Y)

	plt.pcolormesh(X, Y, Z, shading='auto')

	plt.plot(x, y, "ok", label="input point")

	plt.legend()

	plt.colorbar()

	plt.axis("equal")

	plt.show()

def dummy(array,meshCoords):
	#print("Python function running successfully")
	#print(type(array),len(array),'\n')
	#array = 2 * array
	#print(type(meshCoords),len(meshCoords),'\n', meshCoords[:,0])
	#print("Python function ended successfully")
	print("hi")
	print(np.array2string(array,separator = ', '))
	print(np.array2string(meshCoords,separator = ', '))
	
	array = array * 1
	x = meshCoords[: , 0]
	y = meshCoords[: , 1]
	X = np.linspace(min(x), max(x))
	Y = np.linspace(min(y), max(y))
	X, Y = np.meshgrid(x, y)
	#z = np.absolute(array)*10000
	z = array *10000
	z = z.T[0]
	#print(np.array2string(z,separator = ', '))
	print(x,y,z)
	print(len(x),len(y),len(z))
	#print(type(z))
	#print(X,Y)
	#s = np.random.rand(len(meshCoords))*200
	#fig = plt.figure()
	#ax = fig.gca(projection = '3d')
	#ax.plot_surface(X, Y, Z, cmap=cm.gray)

	#plt.show()
	#plt.scatter(x, y,s=Z,c=Z, cmap = "Spectral")
	#plt.show()
	
	interp = LinearNDInterpolator(list(zip(x, y)), z)

	Z = interp(X, Y)
	plt.figure()
	plt.pcolormesh(X, Y, Z)

	#plt.plot(x, y, "ok", label="input point")

	#plt.legend()

	plt.colorbar()

	plt.axis("equal")
	
	plt.show()
	return array
	
def python_func1(array, meshCoords):
	dummy(array,meshCoords)
	return 1

def python_func(array, meshCoords):
	try:
		with open("out.txt", "w") as output:
			#print("Python function running successfully")
			#print(type(array),len(array),'\n')
			#array = 2 * array
			#print(type(meshCoords),len(meshCoords),'\n', meshCoords[:,0])
			#print("Python function ended successfully")
			print("hi",file=output)
			#print(np.array2string(array,separator = ', '))
			#print(np.array2string(meshCoords,separator = ', '))
			
		array = array * 1
		x = meshCoords[: , 0]
		y = meshCoords[: , 1]
		X = np.linspace(min(x), max(x))
		Y = np.linspace(min(y), max(y))
		X, Y = np.meshgrid(x, y)
		#z = np.absolute(array)*10000
		z = array *10000
		z = z.T[0]
		#print(np.array2string(z,separator = ', '))
		#print(x,y,z)
		print(len(x),len(y),len(z))
		#print(type(z))
		#print(X,Y)
		#s = np.random.rand(len(meshCoords))*200
		#fig = plt.figure()
		#ax = fig.gca(projection = '3d')
		#ax.plot_surface(X, Y, Z, cmap=cm.gray)

		#plt.show()
		#plt.scatter(x, y,s=Z,c=Z, cmap = "Spectral")
		#plt.show()
		print("after interpolation 1")
		interp = LinearNDInterpolator(list(zip(x, y)), z)
		print("after interpolation 2")
		Z = interp(X, Y)
		#plt.figure()
		print("after interpolation 3")
		#pdb.set_trace()
		plt.pcolormesh(X, Y, Z)
		print("after interpolation 4")

		fig, ax = plt.subplots()
		ax.plot(x, y, "ok", label="input point")
		plt.legend()

		#fig.colorbar()
		ax.grid()
		plt.axis("equal")
		fig.savefig("fig.png")
		#pdb.set_trace()
		#plt.imshow()
		print("after interpolation 5")
		#plt.show()
		print("after interpolation 6")
	except Exception as e:
		print(e)
		traceback.print_exc()
	return array

def random_char(y):
	return ''.join(random.choice(string.ascii_letters) for x in range(y))
	
#this is a test to write to a file
def test_func():
	#print("aslkfjd")
	
	# Data for plotting
	t = np.arange(0.0, 2.0, 0.01)
	print(t)
	s = 1 + np.sin(2 * np.pi * t)

	fig, ax = plt.subplots()
	ax.plot(t, s)

	ax.set(xlabel='time (s)', ylabel='voltage (mV)',
	       title='About as simple as it gets, folks')
	ax.grid()

	fig.savefig("test.png")
	#plt.show()
	
	with open("write_test.txt","w") as f:
		print("test5")
		mytext = random_char(5)
		f.write(mytext)
		f.write(str(s))
	return 5
#python_func(2)
#print(python_func(2))

if 1==2:
	array = np.array(
	[[0.00088265],
 [0.00073574],
 [0.00062308],
 [0.00051921],
 [0.00046026],
 [0.00072066],
 [0.00069417],
 [0.0007402 ],
 [0.00075911],
 [0.0007719 ],
 [0.000654  ],
 [0.00064248],
 [0.00063839],
 [0.00063069],
 [0.00062734],
 [0.00066861],
 [0.00065799],
 [0.00064778],
 [0.0006371 ],
 [0.00063068],
 [0.00071123],
 [0.00067221],
 [0.00062112],
 [0.00057021],
 [0.0005432 ],
 [0.00046022],
 [0.00051909],
 [0.00062291],
 [0.00073556],
 [0.00088233],
 [0.00077204],
 [0.00075954],
 [0.00074086],
 [0.00069419],
 [0.00072093],
 [0.0006278 ],
 [0.00063181],
 [0.00064   ],
 [0.00064511],
 [0.00065586],
 [0.00063033],
 [0.0006358 ],
 [0.00064458],
 [0.00065041],
 [0.00066016],
 [0.00055211],
 [0.00059214],
 [0.00065386],
 [0.000718  ],
 [0.00076032],
 [0.0008197 ],
 [0.0005632 ],
 [0.00042634],
 [0.00033384],
 [0.00029891],
 [0.00066884],
 [0.0005391 ],
 [0.00051113],
 [0.00047667],
 [0.00046047],
 [0.00064534],
 [0.00061207],
 [0.00057817],
 [0.00054055],
 [0.00051511],
 [0.00066677],
 [0.0006527 ],
 [0.00061198],
 [0.00054478],
 [0.00048775],
 [0.00076351],
 [0.00071856],
 [0.00061032],
 [0.00044319],
 [0.0002961 ],
 [0.00029896],
 [0.00033394],
 [0.00042651],
 [0.00056348],
 [0.00082004],
 [0.00046087],
 [0.00047768],
 [0.00051218],
 [0.00053947],
 [0.0006682 ],
 [0.00051513],
 [0.00054091],
 [0.00057886],
 [0.0006128 ],
 [0.00064556],
 [0.00049092],
 [0.00055463],
 [0.00062685],
 [0.00066813],
 [0.00067899],
 [0.0002767 ],
 [0.00040001],
 [0.00055684],
 [0.00066128],
 [0.00070817]]
)
	 
	meshCoords = np.array([[-6.14202583e+00,  3.87792527e+01, -1.74594242e-17],
 [-1.78248521e+01,  3.49832518e+01, -3.56972630e-17],
 [-2.77628591e+01,  2.77628591e+01,  0.00000000e+00],
 [-3.49832518e+01,  1.78248521e+01,  0.00000000e+00],
 [-3.87792527e+01,  6.14202583e+00,  8.72971209e-18],
 [-3.32799596e+00,  2.10121543e+01,  3.97549064e-17],
 [-9.65821991e+00,  1.89553290e+01,  0.00000000e+00],
 [-1.50430307e+01,  1.50430307e+01,  0.00000000e+00],
 [-1.89553290e+01,  9.65821991e+00,  3.04677524e-17],
 [-2.10121543e+01,  3.32799596e+00,  1.73669157e-17],
 [-1.74601908e+00,  1.10239380e+01, -2.04175123e-17],
 [-5.06714449e+00,  9.94483357e+00,  0.00000000e+00],
 [-7.89226285e+00,  7.89226285e+00,  2.71026265e-17],
 [-9.94483357e+00,  5.06714449e+00,  1.31093739e-17],
 [-1.10239380e+01,  1.74601908e+00, -2.04747165e-17],
 [-8.57489452e-01,  5.41397855e+00,  2.31363450e-18],
 [-2.48853124e+00,  4.88401867e+00,  1.11993258e-17],
 [-3.87597841e+00,  3.87597841e+00,  2.42022425e-17],
 [-4.88401867e+00,  2.48853124e+00,  1.21011191e-17],
 [-5.41397855e+00,  8.57489452e-01,  1.41371516e-17],
 [-3.61176204e-01,  2.28037772e+00,  3.43716359e-18],
 [-1.04817419e+00,  2.05715798e+00,  4.17744325e-17],
 [-1.63256962e+00,  1.63256962e+00, -1.42425595e-17],
 [-2.05715798e+00,  1.04817419e+00,  0.00000000e+00],
 [-2.28037772e+00,  3.61176204e-01,  4.15280741e-17],
 [-3.87792527e+01, -6.14202583e+00,  9.50810727e-18],
 [-3.49832518e+01, -1.78248521e+01, -3.56972630e-17],
 [-2.77628591e+01, -2.77628591e+01,  0.00000000e+00],
 [-1.78248521e+01, -3.49832518e+01,  0.00000000e+00],
 [-6.14202583e+00, -3.87792527e+01,  8.72971209e-18],
 [-2.10121543e+01, -3.32799596e+00, -2.45459499e-17],
 [-1.89553290e+01, -9.65821991e+00,  0.00000000e+00],
 [-1.50430307e+01, -1.50430307e+01,  0.00000000e+00],
 [-9.65821991e+00, -1.89553290e+01,  3.04677524e-17],
 [-3.32799596e+00, -2.10121543e+01,  1.73669157e-17],
 [-1.10239380e+01, -1.74601908e+00, -2.82068691e-17],
 [-9.94483357e+00, -5.06714449e+00,  0.00000000e+00],
 [-7.89226285e+00, -7.89226285e+00,  2.71026265e-17],
 [-5.06714449e+00, -9.94483357e+00,  1.31093739e-17],
 [-1.74601908e+00, -1.10239380e+01, -2.04747165e-17],
 [-5.41397855e+00, -8.57489452e-01, -5.04404903e-17],
 [-4.88401867e+00, -2.48853124e+00,  1.11993258e-17],
 [-3.87597841e+00, -3.87597841e+00,  2.42022425e-17],
 [-2.48853124e+00, -4.88401867e+00,  1.21011191e-17],
 [-8.57489452e-01, -5.41397855e+00,  1.41371516e-17],
 [-2.28037772e+00, -3.61176204e-01, -2.82387631e-17],
 [-2.05715798e+00, -1.04817419e+00,  4.17744325e-17],
 [-1.63256962e+00, -1.63256962e+00, -1.42425595e-17],
 [-1.04817419e+00, -2.05715798e+00,  0.00000000e+00],
 [-3.61176204e-01, -2.28037772e+00,  4.15280741e-17],
 [ 6.14202583e+00, -3.87792527e+01,  9.50810727e-18],
 [ 1.78248521e+01, -3.49832518e+01, -3.56972630e-17],
 [ 2.77628591e+01, -2.77628591e+01,  0.00000000e+00],
 [ 3.49832518e+01, -1.78248521e+01,  0.00000000e+00],
 [ 3.87792527e+01, -6.14202583e+00,  0.00000000e+00],
 [ 3.32799596e+00, -2.10121543e+01, -2.45459499e-17],
 [ 9.65821991e+00, -1.89553290e+01,  0.00000000e+00],
 [ 1.50430307e+01, -1.50430307e+01,  0.00000000e+00],
 [ 1.89553290e+01, -9.65821991e+00,  3.04677524e-17],
 [ 2.10121543e+01, -3.32799596e+00, -3.34765836e-17],
 [ 1.74601908e+00, -1.10239380e+01, -2.82068691e-17],
 [ 5.06714449e+00, -9.94483357e+00,  0.00000000e+00],
 [ 7.89226285e+00, -7.89226285e+00,  2.71026265e-17],
 [ 9.94483357e+00, -5.06714449e+00,  1.31093739e-17],
 [ 1.10239380e+01, -1.74601908e+00,  2.04747165e-17],
 [ 8.57489452e-01, -5.41397855e+00, -5.04404903e-17],
 [ 2.48853124e+00, -4.88401867e+00,  1.11993258e-17],
 [ 3.87597841e+00, -3.87597841e+00,  2.42022425e-17],
 [ 4.88401867e+00, -2.48853124e+00,  1.21011191e-17],
 [ 5.41397855e+00, -8.57489452e-01, -1.41371516e-17],
 [ 3.61176204e-01, -2.28037772e+00, -2.82387631e-17],
 [ 1.04817419e+00, -2.05715798e+00,  4.17744325e-17],
 [ 1.63256962e+00, -1.63256962e+00, -1.42425595e-17],
 [ 2.05715798e+00, -1.04817419e+00,  0.00000000e+00],
 [ 2.28037772e+00, -3.61176204e-01, -3.56661904e-18],
 [ 3.87792527e+01,  6.14202583e+00,  0.00000000e+00],
 [ 3.49832518e+01,  1.78248521e+01, -3.56972630e-17],
 [ 2.77628591e+01,  2.77628591e+01,  0.00000000e+00],
 [ 1.78248521e+01,  3.49832518e+01,  0.00000000e+00],
 [ 6.14202583e+00,  3.87792527e+01,  0.00000000e+00],
 [ 2.10121543e+01,  3.32799596e+00,  4.78346521e-17],
 [ 1.89553290e+01,  9.65821991e+00,  0.00000000e+00],
 [ 1.50430307e+01,  1.50430307e+01,  0.00000000e+00],
 [ 9.65821991e+00,  1.89553290e+01,  3.04677524e-17],
 [ 3.32799596e+00,  2.10121543e+01, -2.46676583e-17],
 [ 1.10239380e+01,  1.74601908e+00,  2.73229951e-17],
 [ 9.94483357e+00,  5.06714449e+00,  0.00000000e+00],
 [ 7.89226285e+00,  7.89226285e+00,  2.71026265e-17],
 [ 5.06714449e+00,  9.94483357e+00,  1.31093739e-17],
 [ 1.74601908e+00,  1.10239380e+01, -2.74376701e-17],
 [ 5.41397855e+00,  8.57489452e-01,  1.41371516e-17],
 [ 4.88401867e+00,  2.48853124e+00,  1.11993258e-17],
 [ 3.87597841e+00,  3.87597841e+00,  2.42022425e-17],
 [ 2.48853124e+00,  4.88401867e+00,  1.21011191e-17],
 [ 8.57489452e-01,  5.41397855e+00, -5.04363082e-17],
 [ 2.28037772e+00,  3.61176204e-01,  3.56661908e-18],
 [ 2.05715798e+00,  1.04817419e+00,  4.17744325e-17],
 [ 1.63256962e+00,  1.63256962e+00, -1.42425595e-17],
 [ 1.04817419e+00,  2.05715798e+00,  0.00000000e+00],
 [ 3.61176204e-01,  2.28037772e+00, -3.69607452e-18]]
)
	 
	 
	python_func(array, meshCoords)
	

