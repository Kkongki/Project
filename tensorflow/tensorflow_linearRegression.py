import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

# 선형회귀 분포를 총 1000개 표시하며, 이 값들은 conjunto_puntos에 저장됩니다.
num_puntos = 1000
conjunto_puntos = []

# 함수 y = 0.1x + 0.3에 오차 0 ~ 0.3을 무작위로 추가하여 conjunto_puntos에 저장합니다.
for i in range(num_puntos):
    x1= np.random.normal(0.0, 0.55)
    y1 = x1 * 0.1 + 0.3 + np.random.normal(0.0, 0.03)
    conjunto_puntos.append([x1, y1])

# 머신러닝을 위해 x_data와 y_data를 conjunto_puntos에 저장된 값을 불러와 x, y로 분리합니다.
x_data = [v[0] for v in conjunto_puntos]
y_data = [v[1] for v in conjunto_puntos]

# 머신러닝 학습을 통해 기울기 값인 W, 그리고 오프셋인 b가 조정됩니다. (목표: W = 0.1, b = 0.3)
W = tf.Variable(tf.random.uniform([1], -1.0, 1.0))
b = tf.Variable(tf.zeros([1]))

# 선형회귀 예측을 위한 예측 모델을 만듭니다. (학습이 될수록 예측 모델은 변합니다)
y = W * x_data + b

# 예측 모델이 실제 선형회귀 함수와 최대한 가깝게 만들기 위해 조정합니다.
loss = tf.reduce_mean(tf.square(y - y_data))
optimizer = tf.train.GradientDescentOptimizer(0.5)
train = optimizer.minimize(loss)

# 텐서플로우로 작성한 코드를 데이터흐름을 통해 학습할 공간을 생성합니다.
with tf.compat.v1.Session() as sess:
    
    # 변수 W와 b가 미정된 값이므로 우선 초기화합니다.
    sess.run(tf.global_variables_initializer())

    # 16번의 반복적인 학습을 통해 W와 b 값이 조정되며, 변화를 화면으로 볼 수 있습니다.
    for step in range(16):
        sess.run(train)
        plt.plot(x_data, y_data, 'ro', label='train data')
        plt.plot(x_data, sess.run(W) * x_data + sess.run(b))
        plt.xlim(-2,2); plt.ylim(0.1,0.6)
        plt.xlabel('x'); plt.ylabel('y')
        plt.legend(); plt.show()
