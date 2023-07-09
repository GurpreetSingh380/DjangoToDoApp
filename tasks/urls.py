from django.urls import path
from . import views

urlpatterns=[
    path('', views.index, name='main'),
    path('update/<str:pk>/', views.updateTask, name='update'),
    path('delete/<str:pk>/', views.delete, name='delete'),
    path('login/', views.loginUser, name='login'),
    path('register/', views.register, name='register'),
    path('logout/', views.logoutUser, name='logoutUser'),
    path('showusers/', views.showUsers, name='showusers')
]